/*
Interface class that abstracts client and server

Workflow:
Application --> BackendCommuicator --> Factory --> Server

*/
#pragma once

#include<string>
// abstract layer where application layer depends ONLY on this class.

struct Packet {
    uint32_t seqNum;
    std::string data;
    Packet(uint32_t seqNum, std::string data) : 
            seqNum(seqNum), data(data) 
    {
    }
};

struct Response {
    std::string status;
    std::string result;
    Response(std::string status, std::string result) : 
            status(std::move(status)), result(std::move(result))
    {
    }
};

class BackendCommunicator {

    std::string name; // defined only to demonstrate 'default'
    public:
        // If this default is not specified, name is some garbage. default initialise
        // name string as 'empty' string. name = ""
        BackendCommunicator() = default; 
        
        virtual Response sendPostRequest(const Packet&) = 0;
        virtual void connectServer(const std::string& host, int port) = 0;
        virtual void disconnect() = 0;

        virtual ~BackendCommunicator() = default;
};
