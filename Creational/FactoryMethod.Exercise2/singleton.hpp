#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <mutex>

template <typename T>
class SingletonHolder
{
private:
    SingletonHolder() = default;
    ~SingletonHolder() = default;

public:
    SingletonHolder(const SingletonHolder&) = delete;
    SingletonHolder& operator=(const SingletonHolder&) = delete;

    static T& instance()
    {
        static T unique_instance;

        return unique_instance;
    }
};

namespace Alternative
{
    template <typename T>
    class SingletonHolder
    {
    private:
        SingletonHolder() = default;
        ~SingletonHolder() = default;

        static std::atomic<T*> instance_;
        static std::mutex mtx_instance_;

    public:
        SingletonHolder(const SingletonHolder&) = delete;
        SingletonHolder& operator=(const SingletonHolder&) = delete;

        static T& instance()
        {
            if (!instance_)
            {
                std::lock_guard<std::mutex> lk{mtx_instance_};

                if (!instance_)
                {
                    //instance_ = new T();

                    // 1 - malloc
                    void* raw_mem = ::operator new(sizeof(T));                    
                    
                    // 2 - ctor
                    new (raw_mem) T();                    

                    // 3 - assignment
                    instance_.store(static_cast<T*>(raw_mem));
                }
            }

            return instance;
        }
    };
}

#endif // SINGLETON_HPP
