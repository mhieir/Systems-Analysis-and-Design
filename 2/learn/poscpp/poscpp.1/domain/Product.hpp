#pragma once
#include <string>
#include "Entity.hpp"

class Product : public Entity {
public:
  Product(std::string productCode, std::string description, double price, std::string defaultUnit) {
    productCode_ = productCode;
    description_ = description;
    price_ = price;
    defaultUnit_ = defaultUnit;
  }

  std::string productCode() const { return productCode_; }
  std::string description() const { return description_; }
  double price() const { return price_; }
  std::string defaultUnit() const { return defaultUnit_; }
private:
  std::string productCode_;
  std::string description_;
  double price_;
  std::string defaultUnit_;
};
