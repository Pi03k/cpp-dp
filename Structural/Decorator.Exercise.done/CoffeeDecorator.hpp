#pragma once

#include <memory>
#include "starbugs_coffee.hpp"

class CoffeeDecorator : public CoffeeBase
{
  public:
    CoffeeDecorator(std::unique_ptr<CoffeeBase> coffee, float price, const std::string&description);
    float get_total_price() const
    {
      return coffee->get_total_price() + CoffeeBase::get_total_price();
    }
    std::string get_description() const
    {
      return coffee->get_description() + CoffeeBase::get_description();
    }
    void prepare()
    {
      coffee->prepare();
    }

  private:
    std::unique_ptr<CoffeeBase> coffee;
};

class WhiskeyCoffee : public CoffeeDecorator
{
  public:
    WhiskeyCoffee(std::unique_ptr<CoffeeBase>);
    void prepare() override
    {
      CoffeeDecorator::prepare();
      std::cout << "\tadding whiskey" << std::endl;
    }
}; // class WhiskeyCoffee
