#include "CoffeeDecorator.hpp"

CoffeeDecorator::CoffeeDecorator(std::unique_ptr<CoffeeBase> coffee, float price, const std::string& description)
  : CoffeeBase(price, description), coffee(std::move(coffee))
{
}

WhiskeyCoffee::WhiskeyCoffee(std::unique_ptr<CoffeeBase> coffee)
  : CoffeeDecorator(std::move(coffee), 6, " with whiskey")
{
}
