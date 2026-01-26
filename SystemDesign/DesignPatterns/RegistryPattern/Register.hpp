#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "BackendCommunicator.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
#include <functional>

// Registry - A self-service agency. A new service registers itself without any manual assignment 
//            as in factory pattern

class Register
{
private:
    using Creator = std::function<std::unique_ptr<BackendCommunicator>()>;
    static std::unordered_map<std::string, Creator>& getRegistry()
    {
        std::unordered_map<std::string, Creator> registry;
        return registry;
    }

public:
    Register();
    ~Register();

    template<typename T>
    static void registerToBackend(const std::string& name)
    {   
        // adds class to map when register from backend. backed will class this method
        // eg: HttpCommunicator.cpp - this backend service is registered as following
        // static Register::registerToBackend<HttpCommunicator>("http"); <-- "http" is key for look-up
        getRegister()[name] = []() { return std::make_unique<T>()};
        std::cout<<"Class/Service "<<name<<"Registered..."<<std::endl;
    }

    static std::unique_ptr<BackendCommunicator> create(const std::string& name)
    {
        auto& registry = getRegistry();

        auto it = registry.find(name);
        if (it != registry.end())
        {
            return it->second();
        }
        else
        {
            std::cout<<name<<" not found!!"<<std::endl;
        }
    }
};

Register::Register()
{
    std::cout<<"Init Register"<<std::endl;
}

Register::~Register()
{
    std::cout<<"Destroy Register"<<std::endl;
}

#endif