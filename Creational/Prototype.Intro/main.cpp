#include <cassert>
#include <iostream>
#include <memory>
#include <typeinfo>

using namespace std;

class Engine
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::unique_ptr<Engine> clone() const = 0; // virtual copy ctor
    virtual ~Engine() = default;
};

template <typename EngineType, typename EngineBase = Engine>
class CloneableEngine : public EngineBase
{
public:
    std::unique_ptr<Engine> clone() const override
    {
        return std::make_unique<EngineType>(static_cast<const EngineType&>(*this));
    }
};

class Diesel : public CloneableEngine<Diesel>
{
public:
    virtual void start() override
    {
        cout << "Diesel starts\n";
    }

    virtual void stop() override
    {
        cout << "Diesel stops\n";
    }
};

class TDI : public CloneableEngine<TDI, Diesel>
{
public:
    virtual void start() override
    {
        cout << "TDI starts\n";
    }

    virtual void stop() override
    {
        cout << "TDI stops\n";
    }
};

class Hybrid : public CloneableEngine<Hybrid>
{
public:
    virtual void start() override
    {
        cout << "Hybrid starts\n";
    }

    virtual void stop() override
    {
        cout << "Hybrid stops\n";
    }
};

class Car
{
    std::unique_ptr<Engine> engine_;

public:
    Car(std::unique_ptr<Engine> engine)
        : engine_{move(engine)}
    {
    }

    Car(const Car& source)
        : engine_{source.engine_->clone()}
    {
    }

    Car& operator=(const Car& source)
    {
        if (this != &source)
        {
            engine_ = source.engine_->clone();
        }

        return *this;
    }

    Car(Car&&) = default;
    Car& operator=(Car&&) = default;

    void drive(int km)
    {
        engine_->start();
        cout << "Driving " << km << " kms\n";
        engine_->stop();
    }
};

int main()
{
    Car c1{std::make_unique<TDI>()};
    c1.drive(100);

    cout << "\n";

    Car c2 = c1;
    c2.drive(200);
}
