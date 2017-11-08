#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <functional>

// "Product"
class Logger
{
public:
    // product's interface
    virtual void log(const std::string& msg) = 0;
    virtual ~Logger() {}
};

// "ConcreteProductA"
class FileLogger : public Logger
{
    std::ofstream log_file_;

public:
    FileLogger(const std::string& logname)
        : log_file_{logname, std::ios::app}
    {
    }

    void log(const std::string& msg)
    {
        log_file_ << "LOG: " << msg << std::endl;
    }
};

class DbLogger : public Logger
{
    std::string conn_str_;

public:
    DbLogger(const std::string& conn_str)
        : conn_str_{conn_str}
    {
    }

    void log(const std::string& msg) override
    {
        std::cout << "Logging to db: " << msg << std::endl;
    }
};

// "ConcreteProductB"
class ConsoleLogger : public Logger
{
public:
    void log(const std::string& msg)
    {
        std::cout << "LOG: " << msg << std::endl;
    }
};

using LoggerCreator = std::function<std::unique_ptr<Logger>()>;

class FileLoggerCreator
{
public:
    std::string file_name_;

public:
    FileLoggerCreator(const std::string& file_name)
        : file_name_{file_name}
    {
    }

    std::unique_ptr<Logger> operator()()
    {
        return std::make_unique<FileLogger>(file_name_);
    }
};

namespace Canonical
{
    // "Creator"
    class LoggerCreator
    {
    public:
        virtual std::unique_ptr<Logger> create_logger() = 0; // factory method
        virtual ~LoggerCreator() = default;
    };

    // "ConcreteCreatorA"
    class FileLoggerCreator : public LoggerCreator
    {
        std::string file_name_;

    public:
        FileLoggerCreator(const std::string& file_name)
            : file_name_{file_name}
        {
        }

        virtual std::unique_ptr<Logger> create_logger() override
        {
            return std::make_unique<FileLogger>(file_name_);
        }
    };

    // "ConcreteCreatorB"
    class ConsoleLoggerCreator : public LoggerCreator
    {
    public:
        virtual std::unique_ptr<Logger> create_logger() override
        {
            return std::make_unique<ConsoleLogger>();
        }
    };

    class DbLoggerCreator : public LoggerCreator
    {
    public:
        virtual std::unique_ptr<Logger> create_logger() override
        {
            return std::make_unique<DbLogger>("SqlServer");
        }
    };
}

#endif /*FACTORY_HPP_*/
