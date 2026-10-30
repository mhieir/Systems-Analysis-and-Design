#pragma once
#include <memory>
#include <unordered_map>
#include <list>

class Seq {
public:
  static long next();
private:
  static long last_id_;
};

template<typename T>
class BaseRepository {
public:
  std::shared_ptr<T> save(std::shared_ptr<T> entity) {
    if (!entity->hasId())
      entity->setId(Seq::next());
    items_[entity->id()] = entity;
    return entity;
  }

  std::shared_ptr<T> findById(long id) const {
    auto it = items_.find(id);
    if (it == items_.end()) return nullptr;
    return it->second;
  }

  std::list<std::shared_ptr<T>> findAll() const {
    std::list<std::shared_ptr<T>> result;
    for (const auto& [k, v] : items_)
      result.push_back(v);
    return result;
  }

  bool existsById(long id) const {
    return items_.contains(id);
  }

  void deleteById(long id) {
    items_.erase(id);
  }

  void deleteEntity(std::shared_ptr<T> entity) {
    items_.erase(entity->id());
  }

  void deleteAll() {
    items_.clear();
  }

protected:
  std::unordered_map<long, std::shared_ptr<T>> items_;
};
