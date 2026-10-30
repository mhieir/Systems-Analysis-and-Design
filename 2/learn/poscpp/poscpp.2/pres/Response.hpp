#pragma once
#include <optional>

enum Status {OK, NOT_FOUND};

template<typename T>
class Response {
public:
  Response(Status status, std::optional<T> body, std::string message) 
    : status_(status), body_(body), message_(message) {}
  Response(std::optional<T> body) : Response(Status::OK, body, "") {}
  Response(Status status, std::string message) : Response(status, std::nullopt, message) {}
  
  Status status() { return status_; }
  std::optional<T> body() { return body_; }
  std::string message() { return message_; }
private:
  Status status_;
  std::optional<T> body_;
  std::string message_;
};
