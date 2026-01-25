
#include "Factory.hpp"


std::unique_ptr<BackendCommunicator> Factory::createBackendServer(const std::string& type)
{
    if ( type == "http")
    {
        return std::unique_ptr<HTTPCommunicator>();
    }else{
        std::cout<<"Only Http communicator is suppoted"<<std::endl;
        return nullptr;
    }
}
