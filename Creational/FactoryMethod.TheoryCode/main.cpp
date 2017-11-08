#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

#include "factory.hpp"

using namespace std;

namespace Canonical
{
    class Service
    {
        shared_ptr<LoggerCreator> creator_;

    public:
        Service(shared_ptr<LoggerCreator> creator)
            : creator_(creator)
        {
        }

        Service(const Service&) = delete;
        Service& operator=(const Service&) = delete;

        void use()
        {
            unique_ptr<Logger> logger = creator_->create_logger();
            logger->log("Client::use() has been started...");
            run();
            logger->log("Client::use() has finished...");
        }

    protected:
        virtual void run() {}
    };
}

class Service
{
    LoggerCreator creator_;

public:
    Service(LoggerCreator creator)
        : creator_(creator)
    {
    }

    Service(const Service&) = delete;
    Service& operator=(const Service&) = delete;

    void use()
    {
        unique_ptr<Logger> logger = creator_();
        logger->log("Client::use() has been started...");
        run();
        logger->log("Client::use() has finished...");
    }

protected:
    virtual void run() {}
};

using LoggerFactory = std::unordered_map<std::string, LoggerCreator>;

int main()
{
    LoggerFactory logger_factory;
    logger_factory.insert(make_pair("ConsoleLogger", &std::make_unique<ConsoleLogger>));
    logger_factory.insert(make_pair("FileLogger", FileLoggerCreator{"data.log"}));
    //logger_factory.insert(make_pair("DbLogger", [] { return std::make_unique<DbLogger>("SqlServer"); }));
    logger_factory.insert(make_pair("DbLogger", [] { return std::unique_ptr<DbLogger>(new DbLogger("SqlServer")); }));

    Service srv(logger_factory.at("DbLogger"));
    srv.use();
}

void most_frequent_useage_of_factory_method()
{
    list<int> container = { 1, 3, 4 };

    for (const auto& item : container)
        cout << item << endl;

    for (auto it = container.begin(); it != container.end(); ++it)
    {
        const auto& item = *it;
        cout << item << endl;
    }
}
