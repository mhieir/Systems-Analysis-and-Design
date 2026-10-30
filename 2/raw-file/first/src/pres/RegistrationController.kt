package pres

import data.CourseGroupRepository
import data.CourseRepository
import data.StudentRepository
import domain.CourseGroup
import domain.RegistrationRequirement
import domain.RegistrationStatus

class RegistrationController(
    private val studentRepo: StudentRepository,
    private val groupRepo: CourseGroupRepository,
    private val courseRepo: CourseRepository,
    private val requirements: List<RegistrationRequirement>
) {

    private fun createView(group: CourseGroup, courseTitle: String): CourseGroupView {
        return CourseGroupView(
            groupId = group.id(),
            courseTitle = courseTitle,
            professorName = group.professorName(),
            availableSeats = group.availableSeats(),
            classSchedule = "${group.classTime().dayOfWeek} ${group.classTime().startTime}-${group.classTime().endTime}"
        )
    }

    fun getAvailableGroups(): Response<List<CourseGroupView>> {
        val views = groupRepo.findAll().map { group ->
            val course = courseRepo.findById(group.courseId())
            createView(group, course?.title() ?: "Unknown")
        }
        return Response(true, "Available groups retrieved", views)
    }

    fun takeGroup(studentId: Long, groupId: Long): Response<CourseGroupView> {
        val student = studentRepo.findById(studentId) ?: return Response(false, "Student not found")
        val group = groupRepo.findById(groupId) ?: return Response(false, "Group not found")
        val course = courseRepo.findById(group.courseId()) ?: return Response(false, "Course not found")
        val allGroups = groupRepo.findAll()

        for (req in requirements) {
            if (!req.isSatisfiedBy(student, group, course, allGroups)) {
                return Response(false, "Registration failed due to rule: ${req::class.simpleName}")
            }
        }
        if (group.isFull()) {
            return Response(false, "Group is full. You can join the waitlist.")
        }
        group.enroll(studentId)
        student.changeRegistrationStatus(groupId, RegistrationStatus.REGISTERED)
        groupRepo.save(group)
        studentRepo.save(student)

        return Response(true, "Successfully registered", createView(group, course.title()))
    }

    fun dropGroup(studentId: Long, groupId: Long): Response<String> {
        val student = studentRepo.findById(studentId) ?: return Response(false, "Student not found")
        val group = groupRepo.findById(groupId) ?: return Response(false, "Group not found")

        group.unenroll(studentId)
        student.removeRegistration(groupId)

        val nextStudentId = group.getNextInWaitlist()
        if (nextStudentId != null) {
            val luckyStudent = studentRepo.findById(nextStudentId)
            if (luckyStudent != null) {
                group.enroll(nextStudentId)
                luckyStudent.changeRegistrationStatus(groupId, RegistrationStatus.REGISTERED)
                studentRepo.save(luckyStudent)
            }
        }

        groupRepo.save(group)
        studentRepo.save(student)

        return Response(true, "Successfully dropped group")
    }

    fun joinWaitlist(studentId: Long, groupId: Long): Response<String> {
        val student = studentRepo.findById(studentId) ?: return Response(false, "Student not found")
        val group = groupRepo.findById(groupId) ?: return Response(false, "Group not found")

        if (!group.isFull()) {
            return Response(false, "Group is not full. You can register directly.")
        }

        group.addToWaitlist(studentId)
        student.changeRegistrationStatus(groupId, RegistrationStatus.WAITLISTED)

        groupRepo.save(group)
        studentRepo.save(student)

        return Response(true, "Successfully added to waitlist")
    }
}