#include "starbugs_coffee.hpp"
#include <cassert>
#include <memory>

void client(std::unique_ptr<Coffee> coffee)
{
    std::cout << "Description: " << coffee->get_description() << "; Price: " << coffee->get_total_price() << std::endl;
    coffee->prepare();
}

namespace Starbugs
{
    inline namespace VariadicTemplates
    {
        template <typename HeadDecorator, typename... TailDecorators>
        struct DecorateWith
        {
            static std::unique_ptr<Coffee> make_decorator(std::unique_ptr<Coffee> component)
            {
                auto decorator_component = std::make_unique<HeadDecorator>(move(component));

                return DecorateWith<TailDecorators...>::make_decorator(move(decorator_component));
            }
        };

        template <typename HeadDecorator>
        struct DecorateWith<HeadDecorator>
        {
            static std::unique_ptr<Coffee> make_decorator(std::unique_ptr<Coffee> component)
            {
                return std::make_unique<HeadDecorator>(move(component));
            }
        };

        class CoffeeBuilder
        {
            std::unique_ptr<Coffee> coffee_;

        public:
            template <typename BaseCoffee>
            CoffeeBuilder& create_base()
            {
                coffee_ = std::make_unique<BaseCoffee>();

                return *this;
            }

            template <typename... Condiments>
            CoffeeBuilder& add()
            {
                assert(coffee_);

                coffee_ = DecorateWith<Condiments...>::make_decorator(move(coffee_));

                return *this;
            }

            std::unique_ptr<Coffee> get_coffee()
            {
                return move(coffee_);
            }
        };
    }
}

int main()
{
    using namespace std;

    unique_ptr<Coffee> cf = make_unique<WhippedCream>(
        make_unique<Whisky>(
            make_unique<Whisky>(
                make_unique<Whisky>(
                    make_unique<ExtraEspresso>(
                        make_unique<Espresso>())))));

    client(std::move(cf));

    cout << "\n\n";

    Starbugs::CoffeeBuilder cb;

    cb.create_base<Espresso>().add<ExtraEspresso>();
    cb.add<Whisky, Whisky, Whisky, WhippedCream>();

    client(cb.get_coffee());
}
