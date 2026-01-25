#pragma once

#include "BackendCommunicator.hpp"
#include "HttpCommunicator.hpp"
#include <iostream>
#include <memory>


class Factory {

    public:
        Factory() = default;
        std::unique_ptr<BackendCommunicator> createBackendServer(const std::string& type);

};


