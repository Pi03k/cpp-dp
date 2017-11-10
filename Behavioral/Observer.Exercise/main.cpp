#include "stock.hpp"

using namespace std;

int main()
{
    Stock misys("Misys", 340.0);
    Stock ibm("IBM", 245.0);
    Stock tpsa("TPSA", 95.0);

    std::shared_ptr<Investor> Kulczyk = std::make_shared<Investor>("Kulczyk");
    {
        std::shared_ptr<Investor> Dziedzic = std::make_shared<Investor>("Dziedzic");

        misys.attach(Kulczyk);
        misys.attach(Dziedzic);

        // zmian kursow
        misys.set_price(360.0);
        ibm.set_price(210.0);
        tpsa.set_price(45.0);

        misys.detach(Kulczyk);
    }

    cout << "\n\n";
    
    misys.set_price(380.0);
    ibm.set_price(230.0);
    tpsa.set_price(15.0);
}
