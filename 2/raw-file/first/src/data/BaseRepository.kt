package data

import domain.Entity

abstract class BaseRepository<T : Entity> {
    protected val items = mutableMapOf<Long, T>()
    private var nextId: Long = 1L

    fun save(item: T) {
        if (!item.hasId()) {
            item.setId(nextId)
            nextId++
        }
        items[item.id()] = item
    }

    fun findById(id: Long): T? {
        return items[id]
    }

    fun findAll(): List<T> {
        return items.values.toList()
    }
}