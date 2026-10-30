package pres

data class CourseGroupView(
    val groupId: Long,
    val courseTitle: String,
    val professorName: String,
    val availableSeats: Int,
    val classSchedule: String
)
