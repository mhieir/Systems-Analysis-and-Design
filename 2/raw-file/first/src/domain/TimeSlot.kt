package domain

data class TimeSlot(
    val dayOfWeek : WeekDays,
    val startTime : String,
    val endTime : String
) {
    fun overLapsWith(anotherTimeSlot: TimeSlot) : Boolean {
        if (this.dayOfWeek != anotherTimeSlot.dayOfWeek) {
            return false
        }
        return startTime < anotherTimeSlot.endTime && anotherTimeSlot.startTime < endTime
    }
}