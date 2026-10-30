#include <memory>
#include "ProductRepository.hpp"

std::shared_ptr<ProductRepository> ProductRepository::repo_ = nullptr;

std::shared_ptr<Product> ProductRepository::findByProductCode(std::string productCode) {
  for (const auto& [k, v] : items_) {
    if (v->productCode() == productCode)
      return v;
  }
  return nullptr;
}
