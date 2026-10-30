#pragma once
#include "BaseRepository.hpp"
#include "../domain/Sale.hpp"

class SaleRepository : public BaseRepository<Sale> {
public:
  static std::shared_ptr<SaleRepository> repo() {
    if (repo_ == nullptr)
      repo_ = std::make_shared<SaleRepository>();
    return repo_;
  }

private:
  static std::shared_ptr<SaleRepository> repo_;
};
