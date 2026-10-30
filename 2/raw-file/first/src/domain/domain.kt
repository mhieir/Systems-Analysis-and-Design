package domain

interface RegistrationRequirement {
    fun isSatisfiedBy(student: Student, group: CourseGroup, course: Course, allGroups: List<CourseGroup>): Boolean
}

class PrerequisitesMetRequirement : RegistrationRequirement {
    override fun isSatisfiedBy(student: Student, group: CourseGroup, course: Course, allGroups: List<CourseGroup>): Boolean {
        return course.prerequisites().all { student.hasPassed(it) }
    }
}

class CourseNotPreviouslyPassedRequirement : RegistrationRequirement {
    override fun isSatisfiedBy(student: Student, group: CourseGroup, course: Course, allGroups: List<CourseGroup>): Boolean {
        return !student.hasPassed(course.id())
    }
}

class NoDuplicateGroupRequirement : RegistrationRequirement {
    override fun isSatisfiedBy(student: Student, group: CourseGroup, course: Course, allGroups: List<CourseGroup>): Boolean {
        val registeredIds = student.getRegisteredGroupIds()
        val activeGroups = allGroups.filter { it.id() in registeredIds }
        return activeGroups.none { it.courseId() == course.id() }
    }
}

class NoTimeConflictRequirement : RegistrationRequirement {
    override fun isSatisfiedBy(student: Student, group: CourseGroup, course: Course, allGroups: List<CourseGroup>): Boolean {
        val registeredIds = student.getRegisteredGroupIds()
        val activeGroups = allGroups.filter { it.id() in registeredIds }
        val hasClassConflict = activeGroups.any { it.classTime().overLapsWith(group.classTime()) }
        val hasExamConflict = activeGroups.any { it.examTime().overLapsWith(group.examTime()) }
        return !hasClassConflict && !hasExamConflict
    }
}