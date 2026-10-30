#pragma once
#include <string>
#include <list>
#include "../domain/Sale.hpp"
#include "../domain/DateTime.hpp"
#include "Response.hpp"

struct SaleView {
  long saleId;
  DateTime dateTime;
};

struct SalesLineItemView {
  std::string productCode;
  std::string description;
  double quantity;
  std::string unit;
  double unitPrice;
  double lineTotal;

  SalesLineItemView(const SalesLineItem& line) {
    productCode = line.product()->productCode();
    description = line.product()->description();
    quantity = line.quantity().amount();
    unit = line.quantity().unit();
    unitPrice = line.product()->price();
    lineTotal = line.total();
  }
};

struct InvoiceView {
  long saleId;
  DateTime dateTime;
  std::list<SalesLineItemView> lines;
  double total;

  InvoiceView(const Sale& sale) 
    : saleId(sale.id()), dateTime(sale.dateTime()) {
    for (auto line : sale.lines()) {
      lines.push_back(SalesLineItemView(*line));
    }
    total = sale.total();
  }
};

class SaleController {
public:
  Response<SaleView> makeNewSale();
  Response<SalesLineItemView> enterItem(long currentSaleId, std::string productCode, double quantityAmount);
  Response<InvoiceView> endSale(long currentSaleId);
};
