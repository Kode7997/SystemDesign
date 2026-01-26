#include "HttpCommunicator.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>


HTTPCommunicator::HTTPCommunicator()
{
    std::cout<<"Http communicator Init"<<std::endl;
}
        
void HTTPCommunicator::connectServer(const std::string& host, int port) {
            
            socketfd = socket(AF_INET, SOCK_STREAM, 0);

            if (socketfd == -1){
                throw std::runtime_error("Failed to initialise the socket");
            }

            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            inet_pton(AF_INET, host.c_str(), &addr.sin_addr);

            if (connect(socketfd, (sockaddr *)&addr, sizeof(addr)) < 0){
                throw std::runtime_error("Failed to connect to server");
            }

            std::cout<<"Socket connection successful\n"<<"host: "<<host<<" port: "<<port<<std::endl;
}

Response HTTPCommunicator::sendPostRequest(const Packet& pkt) {
            // HTTP Request
            std::string req = 
                "POST /api/packet HTTP/1.1\r\n"
                "Host: localhost\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: " + std::to_string(pkt.data.size() + 20) + "\r\n"
                "\r\n{\"seq\":" + std::to_string(pkt.seqNum) + ",\"data\":\"" +  pkt.data + "\"}";
            
            send(socketfd, req.c_str(), req.size(), 0);
            
            // response
            char buffer[1024];

            int bytes = recv(socketfd, buffer, sizeof(buffer) - 1, 0);

            buffer[bytes] = '\0';

            // Extract body
            const char *body = strstr(buffer, "\r\n\r\n");
            std::string payload = body ? body + 4 : buffer;
            
            return Response("HTTP_OK_200", payload);
}

// void HTTPCommunicator::recvResponse () {
//     std::cout<<"Recv response"<<std::endl;
// }


