
#include "Factory.hpp"


std::unique_ptr<BackendCommunicator> Factory::createBackendServer(const std::string& type)
{
    if ( type == "http")
    {   
        return std::make_unique<HTTPCommunicator>();;

    }else{
        std::cout<<"Only Http communicator is suppoted"<<std::endl;
        return nullptr;
    }
}
