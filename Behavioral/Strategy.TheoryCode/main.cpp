#include "strategy.hpp"

int main()
{
    DataContext data{UpperCaseFormatter{}};
    data.pretty_print();

    auto lcf = LowerCaseFormatter{};
    data.reset_formatter(lcf);
    data.pretty_print();

    data.reset_formatter(CapitalizeFormatter{});
    data.pretty_print();
}
