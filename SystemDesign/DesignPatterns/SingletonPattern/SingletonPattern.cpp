#include<iostream>
#include "SingletonPattern.hpp"

int main(){

    auto& instance1 = Singleton::getInstance();
    auto& instance2 = Singleton::getInstance();

    if (&instance1 == &instance2){          // address or reference is compared
        std::cout<<"Single Instance"<<std::endl;
    }else{
        std::cout<<"not single instance"<<std::endl;
    }

    return 0;
}