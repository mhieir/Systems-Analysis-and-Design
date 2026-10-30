#pragma once

class Entity {
public:
  Entity() : id_(0) {}
  long id() const { return id_; }
  void setId(long id) { id_ = id; };
  bool hasId() const { return id_ != 0; }
protected:
  long id_;
};
