#pragma once
#include <stdexcept>

class SpecialOffer {
public:
  virtual double discountOn(double amount, double price) const = 0;
};

class TakeMPayForN : public SpecialOffer {
public:
  TakeMPayForN(double m, double n) : m_(m), n_(n) {
    if (m <= 0 || n <= 0 || m <= n)
      throw std::invalid_argument("Invalid arguments for TakeMPayForN");
  }
  double m() const { return m_; }
  double n() const { return n_; }
  double discountOn(double amount, double price) const {
    int div = (int)(amount / m_);
    return div * (m_ - n_) * price;
  }
private:
  double m_;
  double n_;
};

class TakeMForAmount : public SpecialOffer {
public:
  TakeMForAmount(double m, double amount) : m_(m), amount_(amount) {
    if (m <= 0 || amount < 0)
      throw std::invalid_argument("Invalid arguments for TakeMForAmount");
  }
  double m() const { return m_; }
  double amount() const{ return amount_; }
  double discountOn(double amount, double price) const {
    int div = (int)(amount / m_);
    return div * (m_ * price - amount_);
  }
private:
  double m_;
  double amount_;
};

class PercentDiscount : public SpecialOffer {
public:
  PercentDiscount(double percent) : percent_(percent) {
    if (percent < 0 || percent > 100)
      throw std::invalid_argument("Invalid value for percent");
  }
  double percent() const { return percent_; }
  double discountOn(double amount, double price) const {
    return price * percent_;
  }
private:
  double percent_;
};