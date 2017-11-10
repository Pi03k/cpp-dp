#include "stock.hpp"

using namespace std;

int main()
{
    Stock misys("Misys", 340.0);
    Stock ibm("IBM", 245.0);
    Stock tpsa("TPSA", 95.0);

    // rejestracja inwestorow zainteresowanych powiadomieniami o zmianach kursu spolek
    // TODO:
    Observer::Ptr seller = make_shared<Investor>("Zenon");
    Observer::Ptr noob = make_shared<Investor>("Noob");

    misys.watch(seller);
    ibm.watch(seller);
    misys.watch(noob);
    tpsa.watch(noob);

    // zmian kursow
    misys.set_price(360.0);
    ibm.set_price(210.0);
    tpsa.set_price(45.0);

    // IBM closing up
    ibm.unwatch(seller);
    ibm.unwatch(noob);

    misys.set_price(380.0);
    ibm.set_price(230.0);
    tpsa.set_price(15.0);
}
