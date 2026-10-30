package domain

abstract class Entity (id: Long) {
    private var id: Long = 0
    fun id(): Long = id
    fun hasId(): Boolean = id != 0L
    fun setId(newId : Long) {id = newId}
}