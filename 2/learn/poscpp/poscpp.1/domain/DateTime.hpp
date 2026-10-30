#pragma once
#include <chrono>
#include <ctime>
#include <string>

class DateTime {
public:
  static DateTime now() {
    return DateTime(std::chrono::system_clock::now());
  }
  std::string toString() const {
    time_t t = std::chrono::system_clock::to_time_t(dateTime_);
    return ctime(&t);
  }
private:
  DateTime(std::chrono::system_clock::time_point dateTime) : dateTime_(dateTime) {}
  std::chrono::system_clock::time_point dateTime_;
};