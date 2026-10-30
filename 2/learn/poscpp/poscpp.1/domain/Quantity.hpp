#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

class Quantity {
public:
  Quantity(double amount, const std::string& unit)
    : amount_(amount), unit_(unit) {
    if (amount < 0.0)
      throw std::invalid_argument("Quantity must be non-negative");
    if (unit.empty())
      throw std::invalid_argument("Unit must not be empty");
  }

  static Quantity of(double amount, const std::string& unit) {
    return Quantity(amount, unit);
  }

  double amount() const { return amount_; }
  const std::string& unit() const { return unit_; }

  Quantity operator+(const Quantity& other) const {
    checkUnit(other);
    return Quantity(amount_ + other.amount_, unit_);
  }
  Quantity operator-(const Quantity& other) const {
    checkUnit(other);
    double newAmount = amount_ - other.amount_;
    if (newAmount < 0.0)
      throw std::invalid_argument("Resulting quantity is negative");
    return Quantity(newAmount, unit_);
  }
  Quantity operator*(double factor) const {
    return Quantity(amount_ * factor, unit_);
  }
  Quantity operator/(double divisor) const {
    if (std::abs(divisor) < 1e-9)
      throw std::invalid_argument("Division by zero");
    return Quantity(amount_ / divisor, unit_);
  }
  bool operator==(const Quantity& other) const {
    return std::abs(amount_ - other.amount_) < 1e-9 && unit_ == other.unit_;
  }
  bool operator!=(const Quantity& other) const {
    return !(*this == other);
  }
  friend std::ostream& operator<<(std::ostream& os, const Quantity& q) {
    os << q.amount_ << " " << q.unit_;
    return os;
  }

private:
  double amount_;
  std::string unit_;

  void checkUnit(const Quantity& other) const {
    if (unit_ != other.unit_) {
      throw std::invalid_argument("Units must match for this operation");
    }
  }
};
