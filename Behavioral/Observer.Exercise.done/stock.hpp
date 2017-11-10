#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Stock;

class Observer
{
  public:
    virtual void update(const Stock&) = 0;
    virtual ~Observer() = default;
    using Ptr = shared_ptr<Observer>;
};

// Subject
class Stock
{
  private:
    std::string symbol_;
    double price_;
    // kontener przechowywujacy obserwatorow. TODO change to set to avoid duplicates.
    vector<Observer::Ptr> observers;
  public:
    Stock(const std::string& symbol, double price) : symbol_(symbol), price_(price)
  {
  }

    std::string get_symbol() const
    {
      return symbol_;
    }

    double get_price() const
    {
      return price_;
    }

    // rejestracja obserwatora
    void watch(Observer::Ptr observer)
    {
      observers.push_back(observer);
    }

    // wyrejestrowanie obserwatora
    void unwatch(Observer::Ptr observer)
    {
      vector<Observer::Ptr>::iterator it = std::find(begin(observers), end(observers), observer);
      if (it == observers.end()) { return; }
      else
        observers.erase(it);
    }

    void set_price(double price)
    {
      price_ = price;
      // powiadomienie inwestorow o zmianie kursu...
      for_each(observers.begin(), observers.end(),
          [this] (Observer::Ptr observer) { observer->update(*this); }
          );

    }
};

class Investor : public Observer
{
  std::string name_;

  public:
  Investor(const std::string& name) : name_(name)
  {
  }

  void update(const Stock& stock)
  {
    cout << "Yo! " << name_ << "! Stock " << stock.get_symbol() << " has changed."
      << endl;
  }
};

#endif /*STOCK_HPP_*/
