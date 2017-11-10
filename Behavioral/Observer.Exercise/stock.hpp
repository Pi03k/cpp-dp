#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <iostream>
#include <string>
#include <set>
#include <memory>

using EventArgs = std::string;

class Observer
{
public:
    virtual void update(EventArgs info) = 0;
    virtual ~Observer()
    {
    }
};

using ObserverPtr = std::weak_ptr<Observer>;

class Subject
{
    std::set<ObserverPtr, std::owner_less<ObserverPtr>> observers_;
public:
    void attach(ObserverPtr observer)
    {
        observers_.insert(observer);
    }

    void detach(ObserverPtr observer)
    {
        observers_.erase(observer);
    }
protected:
    void notify(std::string info)
    {
        for (const auto & observer : observers_)
        {
            auto living_observer = observer.lock();
            if (living_observer)
                living_observer->update(info);
        }
    }
};

// Subject
class Stock : public Subject
{
private:
    std::string symbol_;
    double price_;

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

    void set_price(double price)
    {
        if (price_ != price)
        {
            notify(std::to_string(price));
            price_ = price;
        }        
    }
};

class Investor : public Observer
{
    std::string name_;

public:
    Investor(const std::string& name) : name_(name)
    {
    }

    void update(std::string info)
    {
        std::cout << name_ << " price changed to: " << info << std::endl;
    }
};

#endif /*STOCK_HPP_*/
