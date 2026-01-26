#pragma once

#include "BackendCommunicator.hpp"

class HTTPCommunicator : public BackendCommunicator {

    private:
        int socketfd = -1;

    public:
        HTTPCommunicator();
        
        void connectServer(const std::string& host, int port);
        Response sendPostRequest(const Packet& pkt);
        //void recvResponse() override;
};
