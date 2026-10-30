#pragma once
#include <string>
#include <memory>
#include "Entity.hpp"
#include "SpecialOffer.hpp"

class Product : public Entity {
public:
  Product(std::string productCode, std::string description, double price, std::string defaultUnit, std::shared_ptr<SpecialOffer> specialOffer = nullptr) :
    productCode_(productCode),
    description_(description),
    price_(price),
    defaultUnit_(defaultUnit),
    specialOffer_(specialOffer) {}

  std::string productCode() const { return productCode_; }
  std::string description() const { return description_; }
  double price() const { return price_; }
  std::string defaultUnit() const { return defaultUnit_; }
  std::shared_ptr<SpecialOffer> specialOffer() const { return specialOffer_; }
private:
  std::string productCode_;
  std::string description_;
  double price_;
  std::string defaultUnit_;
  std::shared_ptr<SpecialOffer> specialOffer_;
};
