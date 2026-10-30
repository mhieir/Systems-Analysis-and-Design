package domain

class CourseGroup (
    id : Long = 0L,
    private val courseId : Long,
    private val capacity : Int,
    private val professorName : String,
    private  val classTime : TimeSlot,
    private val examTime : TimeSlot,
    private val registeredStudents: MutableList<Long> = mutableListOf(),
    private val waitlist: ArrayDeque<Long> = ArrayDeque()
) : Entity(id) {

    fun capacity() : Int = capacity
    fun professorName() : String = professorName
    fun courseId() : Long = courseId
    fun classTime() : TimeSlot = classTime
    fun examTime() : TimeSlot = examTime
    fun availableSeats() : Int = this.capacity - this.registeredStudents.size
    fun isFull(): Boolean = registeredStudents.size >= capacity
    fun enroll(studentId: Long) {
        if (!registeredStudents.contains(studentId)) {
            registeredStudents.add(studentId)
        }
        waitlist.remove(studentId)
    }
    fun unenroll(studentId: Long) {
        registeredStudents.remove(studentId)
    }
    fun addToWaitlist(studentId: Long) {
        if (!waitlist.contains(studentId) && !registeredStudents.contains(studentId)) {
            waitlist.addLast(studentId)
        }
    }
    fun removeFromWaitlist(studentId: Long) {
        waitlist.remove(studentId)
    }
    fun getNextInWaitlist(): Long? = waitlist.firstOrNull()
}
