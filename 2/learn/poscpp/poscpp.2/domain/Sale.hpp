#pragma once
#include <string>
#include <memory>
#include <list>
#include <chrono>
#include "Product.hpp"
#include "Quantity.hpp"
#include "DateTime.hpp"

class SalesLineItem {
public:
  SalesLineItem(std::shared_ptr<Product> product, Quantity quantity) 
    : product_(product), quantity_(quantity) {}
    Quantity quantity() const { return quantity_; }
    std::shared_ptr<Product> product() const { return product_; }
    
    double total() const { 
      auto specialOffer = product_->specialOffer();
      double discount = 0;
      if (specialOffer != nullptr)
        discount = specialOffer->discountOn(quantity_.amount(), product_->price());
      return quantity_.amount() * product_->price() - discount;
    }
private:
  std::shared_ptr<Product> product_;
  Quantity quantity_;
};

class Sale : public Entity {
public:
  Sale() : dateTime_(DateTime::now()) {}
  std::shared_ptr<SalesLineItem> addItem(std::shared_ptr<Product> product, Quantity quantity) {
    auto line = std::make_shared<SalesLineItem>(product, quantity);
    lines_.push_back(line);
    return line;
  }
  DateTime dateTime() const { return dateTime_; }
  std::list<std::shared_ptr<SalesLineItem>> lines() const { return lines_; }
  double total() const {
    double result = 0;
    for (auto line : lines_) {
      result += line->total();
    }
    return result;
  }
private:
  DateTime dateTime_;
  std::list<std::shared_ptr<SalesLineItem>> lines_;
};
