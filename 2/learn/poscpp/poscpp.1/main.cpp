#include <iostream>
#include "pres/SaleController.hpp"
#include "data/ProductRepository.hpp"

void initData() {
  auto repo = ProductRepository::repo();
  repo->save(std::make_shared<Product>("xy-100", "Black Pencil", 1000, "PCS"));
  repo->save(std::make_shared<Product>("xy-101", "Eraser", 2500, "PCS"));
  repo->save(std::make_shared<Product>("xy-102", "Pencil Sharpener", 3000, "PCS"));
}

std::ostream& operator<<(std::ostream& out, const SalesLineItemView& line) {
  out << "Product Code: " << line.productCode << std::endl 
      << "Description:  " << line.description << std::endl
      << "Quantity:     " << line.quantity << ' ' << line.unit << std::endl
      << "Unit Price:   " << line.unitPrice << std::endl
      << "Line Total:   " << line.lineTotal << std::endl << std::endl;
  return out;
}

std::ostream& operator<<(std::ostream& out, const InvoiceView& invoice) {
  out << "Date and Time : " << invoice.dateTime.toString() << std::endl;
  for (auto line : invoice.lines) {
    out << line;
  }
  out << "Total : " << invoice.total << std::endl;
  return out;
}

int main() {
  initData();

  SaleController saleCtrl;

  auto resp1 = saleCtrl.makeNewSale();
  long saleId = 0;
  if (resp1.body().has_value()) {
    saleId = resp1.body().value().saleId;
    DateTime dateTime = resp1.body().value().dateTime;
    std::cout << "Sale created successfully at " << dateTime.toString() << std::endl;
  } else {
    std::cerr << "Failed to create sale" << std::endl;
    return -1;
  }

  auto resp2 = saleCtrl.enterItem(saleId, "xy-100", 5);
  if (resp2.body().has_value()) {
    auto lineItemView = resp2.body().value();
    std::cout << "Item added successfully\n" << std::endl;
  } else {
    std::cerr << resp2.message() << std::endl;
  }

  auto resp3 = saleCtrl.enterItem(saleId, "xy-101", 1);
  if (resp3.body().has_value()) {
    auto lineItemView = resp3.body().value();
    std::cout << "Item added successfully\n" << std::endl;
  } else {
    std::cerr << resp3.message() << std::endl;
  }

  auto resp4 = saleCtrl.endSale(saleId);
  if (resp4.body().has_value()) {
    auto invoiceView = resp4.body().value();
    std::cout << invoiceView;
  } else {
    std::cerr << resp4.message() << std::endl;
  }
}