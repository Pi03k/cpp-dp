#include "starbugs_coffee.hpp"
#include "CoffeeDecorator.hpp"
#include <memory>

void client(std::unique_ptr<Coffee> coffee)
{
  std::cout << "Description: " << coffee->get_description() << "Price: " << coffee->get_total_price() << std::endl;
  coffee->prepare();
}

int main()
{
  std::unique_ptr<Coffee> cf = std::make_unique<WhiskeyCoffee>(std::make_unique<Espresso>());
  //std::unique_ptr<Coffee> cf = std::make_unique<Coffee>(coffee);
  client(std::move(cf));
}
