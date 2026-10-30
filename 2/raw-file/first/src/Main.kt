import data.*
import domain.*
import pres.*

fun main() {

    val studentRepo = StudentRepository()
    val courseRepo = CourseRepository()
    val groupRepo = CourseGroupRepository()

    val requirements = listOf(
        PrerequisitesMetRequirement(),
        CourseNotPreviouslyPassedRequirement(),
        NoDuplicateGroupRequirement(),
        NoTimeConflictRequirement()
    )

    val controller = RegistrationController(studentRepo, groupRepo, courseRepo, requirements)

    println("\n[SYSTEM] Seeding Database...")

    val math1 = Course(title = "Math 1", prerequisites = emptyList())
    val physics = Course(title = "Physics 1", prerequisites = emptyList())
    courseRepo.save(math1)
    courseRepo.save(physics)

    val math2 = Course(title = "Math 2", prerequisites = listOf(math1.id()))
    courseRepo.save(math2)

    val mahdis = Student(studentNumber = "810102550", name = "Mahdis")
    val bahareh = Student(studentNumber = "810102482", name = "Bahareh")

    val rayhaneh = Student(
        studentNumber = "810102608",
        name = "Rayhaneh",
        passedCourses = mutableListOf(math1.id())
    )

    studentRepo.save(mahdis)
    studentRepo.save(bahareh)
    studentRepo.save(rayhaneh)

    val math1Group1 = CourseGroup(
        courseId = math1.id(), professorName = "Dr. A", capacity = 2,
        classTime = TimeSlot(WeekDays.Saturday, "08:00", "10:00"),
        examTime = TimeSlot(WeekDays.Wednesday, "14:00", "16:00")
    )
    val math1Group2 = CourseGroup(
        courseId = math1.id(), professorName = "Dr. B", capacity = 30,
        classTime = TimeSlot(WeekDays.Sunday, "08:00", "10:00"),
        examTime = TimeSlot(WeekDays.Wednesday, "14:00", "16:00")
    )
    val physicsGroup = CourseGroup(
        courseId = physics.id(), professorName = "Dr. Einstein", capacity = 30,
        classTime = TimeSlot(WeekDays.Saturday, "09:00", "11:00"),
        examTime = TimeSlot(WeekDays.Thursday, "10:00", "12:00")
    )
    val math2Group = CourseGroup(
        courseId = math2.id(), professorName = "Dr. Turing", capacity = 30,
        classTime = TimeSlot(WeekDays.Monday, "10:00", "12:00"),
        examTime = TimeSlot(WeekDays.Tuesday, "10:00", "12:00")
    )

    groupRepo.save(math1Group1)
    groupRepo.save(math1Group2)
    groupRepo.save(physicsGroup)
    groupRepo.save(math2Group)

    fun printResult(testName: String, response: Response<*>) {
        if (response.success) {
            println("✅ [$testName] SUCCESS: ${response.message}")
        } else {
            println("❌ [$testName] BLOCKED: ${response.message}")
        }
    }



    val t1 = controller.takeGroup(mahdis.id(), math1Group1.id())
    printResult("Normal Registration (Mahdis -> Math1 G1)", t1)

    val t2 = controller.takeGroup(mahdis.id(), physicsGroup.id())
    printResult("Time Conflict (Mahdis -> Physics)", t2)

    val t3 = controller.takeGroup(mahdis.id(), math1Group2.id())
    printResult("Duplicate Group (Mahdis -> Math1 G2)", t3)

    val t4 = controller.takeGroup(mahdis.id(), math2Group.id())
    printResult("Missing Prerequisite (Mahdis -> Math 2)", t4)

    val t5 = controller.takeGroup(rayhaneh.id(), math1Group2.id())
    printResult("Already Passed (Rayhaneh -> Math 1)", t5)


    val w1 = controller.takeGroup(bahareh.id(), math1Group1.id())
    printResult("Fill Capacity (Bahareh -> Math1 G1)", w1)

    println("\n--- Rayhaneh tries to register for a full class ---")
    val w2 = controller.takeGroup(rayhaneh.id(), math1Group1.id())
    val newStudent = Student(studentNumber = "9999", name = "TestStudent")
    studentRepo.save(newStudent)

    val w3 = controller.takeGroup(newStudent.id(), math1Group1.id())
    printResult("Over Capacity (TestStudent -> Math1 G1)", w3)
    val w4 = controller.joinWaitlist(newStudent.id(), math1Group1.id())
    printResult("Join Waitlist (TestStudent -> Math1 G1)", w4)
    println("\n--- Mahdis drops the class. Waitlist should promote! ---")
    val w5 = controller.dropGroup(mahdis.id(), math1Group1.id())
    printResult("Drop Course (Mahdis drops Math1 G1)", w5)
    val updatedTestStudent = studentRepo.findById(newStudent.id())
    val isRegisteredNow = updatedTestStudent?.getRegisteredGroupIds()?.contains(math1Group1.id())

    if (isRegisteredNow == true) {
        println("🏆 WAITLIST PROMOTION WORKED! TestStudent was automatically registered.")
    } else {
        println("☠️ WAITLIST FAILED! TestStudent is still waiting.")
    }


}