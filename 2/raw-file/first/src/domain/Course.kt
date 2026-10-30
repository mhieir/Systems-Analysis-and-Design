package domain

class Course(
    id : Long = 0L,
    private val title : String,
    private val prerequisites : List<Long>
) : Entity(id) {

    fun title(): String = title
    fun prerequisites(): List<Long> = prerequisites
}