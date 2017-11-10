#ifndef formatter_HPP_
#define formatter_HPP_

#include <algorithm>
#include <cctype>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// "Strategy"

namespace Canonical
{
    class Formatter
    {
    public:
        virtual std::string format(const std::string& data) = 0;
        virtual ~Formatter() = default;
    };
}

using Formatter = std::function<std::string(const std::string&)>;

// "ConcreteStrategyA"
class UpperCaseFormatter //: public Formatter
{
public:
    std::string operator()(const std::string& data) 
    {
        std::string transformed_data{data};

        std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::toupper(c); });

        return transformed_data;
    }
};

// "ConcreteStrategyB"
class LowerCaseFormatter //: public Formatter
{
public:
    virtual std::string operator()(const std::string& data)// override
    {
        std::string transformed_data{data};

        std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::tolower(c); });

        return transformed_data;
    }
};

// "ConcreteStrategyC"
class CapitalizeFormatter //: public Formatter
{
public:
    virtual std::string operator()(const std::string& data) // override
    {
        std::string transformed_data{data};

        if (data.size() >= 1)
        {
            transformed_data[0] = static_cast<char>(std::toupper(data.front()));

            std::transform(data.begin() + 1, data.end(), transformed_data.begin() + 1, [](char c) { return std::tolower(c); });
        }

        return transformed_data;
    }
};

// "Context"
class DataContext
{
    Formatter formatter_;
    std::string data_ = "text";

public:
    DataContext(Formatter strategy)
        : formatter_{strategy}
    {
    }

    void reset_formatter(Formatter new_formatter)
    {
        formatter_ = new_formatter;
    }

    void pretty_print()
    {
        std::cout << "Data: " << formatter_(data_) << std::endl;
    }

    std::string data() const
    {
        return data_;
    }

    void set_data(const std::string& data)
    {
        data_ = data;
    }
};

#endif /*formatter_HPP_*/
