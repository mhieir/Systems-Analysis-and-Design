#include <memory>
#include "SaleController.hpp"
#include "../domain/Sale.hpp"
#include "../domain/Quantity.hpp"
#include "../data/SaleRepository.hpp"
#include "../data/ProductRepository.hpp"

Response<SaleView> SaleController::makeNewSale() {
  auto newSale = std::make_shared<Sale>();
  SaleRepository::repo()->save(newSale);
  return Response<SaleView>(SaleView{
    newSale->id(), 
    newSale->dateTime()
  });
}

Response<SalesLineItemView> SaleController::enterItem(long currentSaleId, std::string productCode, double quantityAmount) {
  auto currentSale = SaleRepository::repo()->findById(currentSaleId);
  if (currentSale == nullptr)
    return Response<SalesLineItemView>(Status::NOT_FOUND, "Unknown sale ID");
  auto product = ProductRepository::repo()->findByProductCode(productCode);
  if (product == nullptr)
    return Response<SalesLineItemView>(Status::NOT_FOUND, "Unknown product ID");
  
  auto line = currentSale->addItem(product, Quantity::of(quantityAmount, product->defaultUnit()));
  return Response<SalesLineItemView>(SalesLineItemView(*line));
}

Response<InvoiceView> SaleController::endSale(long currentSaleId) {
  auto currentSale = SaleRepository::repo()->findById(currentSaleId);
  if (currentSale == nullptr)
    return Response<InvoiceView>(Status::NOT_FOUND, "Unknown sale ID");
  return Response<InvoiceView>(InvoiceView(*currentSale));
}