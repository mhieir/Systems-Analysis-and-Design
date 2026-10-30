#pragma once
#include <iostream>
#include "BaseRepository.hpp"
#include "../domain/Product.hpp"

class ProductRepository : public BaseRepository<Product> {
public:
  static std::shared_ptr<ProductRepository> repo() {
    if (repo_ == nullptr)
      repo_ = std::make_shared<ProductRepository>();
    return repo_;
  }

  std::shared_ptr<Product> findByProductCode(std::string productCode);

private:
  static std::shared_ptr<ProductRepository> repo_;
};
