package domain

class Student (
    id : Long = 0L,
    private val studentNumber : String,
    private val name : String,
    private  val passedCourses: MutableList<Long> = mutableListOf(),
    private val registrations : MutableList<RegistrationRecord> = mutableListOf()
) : Entity(id) {
    fun name() : String = name
    fun hasPassed(courseId: Long) : Boolean = passedCourses.contains(courseId)
    fun changeRegistrationStatus(groupId: Long, newStatus: RegistrationStatus) {
        val record = registrations.find { it.courseGroupId == groupId }
        if (record != null) {
            record.status = newStatus
        } else {
            registrations.add(RegistrationRecord(groupId, newStatus))
        }
    }
    fun removeRegistration(groupId: Long) {
        registrations.removeIf { it.courseGroupId == groupId }
    }

    fun getRegisteredGroupIds(): List<Long> {
        return registrations
            .filter { it.status == RegistrationStatus.REGISTERED }
            .map { it.courseGroupId }
    }
}