/*

Server class

*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <string>
#include <unordered_map>

class Server {
    private:
        int serverfd = -1;
        int http_port;
        
        std::unordered_map<std::string_view, std::string> apis = {
            {"/api/status", R"({"status":"healthy","uptime":"2h45m"})"},
            {"/api/packet", R"({"processed":true,"seq_received":12345,"action":"routed"})"},
            {"/api/metrics", R"({"packets_processed":1500,"avg_latency":23.4})"},
            {"/tcp/echo", "TCP_ECHO_RESPONSE: Packet processed successfully"}
        };

        std::string handleHttpRequest(const std::string& request){
            
            size_t sPath = request.find(" ");           // start
            size_t ePath = request.find(" ", sPath+1);  // end

            std::string api = request.substr(sPath+1, ePath - sPath - 1);
            
            std::cout<<"Http request path "<<api<<std::endl;

            auto it = apis.find(api);

            if (it != apis.end())
            {
                return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: " +
                   std::to_string(it->second.size()) + "\r\nConnection: close\r\n\r\n" + it->second;
            }
        
            return "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\nConnection: close\r\n\r\nAPI not found";
        }
    public:
        Server(const int port) : http_port(port)
        {
            serverfd = socket(AF_INET, SOCK_STREAM, 0);

            if (serverfd == -1)
            {
                throw std::runtime_error("Failed to create server socket\n");
            }

            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = INADDR_ANY;

            if (bind(serverfd, (sockaddr *)&addr, sizeof(addr)) < 0)
            {
                throw std::runtime_error("Failed bind socket");
                return;
            }

            if (listen(serverfd, 10) < 0)
            {
                throw std::runtime_error("Server not listening");
            }

            std::cout<<"Server runnning on port: "<<std::to_string(port)<<std::endl;
        }

        void run()
        {
            while (true)
            {
                sockaddr_in client_addr;
                socklen_t addr_len = sizeof(client_addr);
                int client_fd = accept(serverfd, (sockaddr *)&client_addr, 
                                &addr_len);
                
                if (client_fd < 0)
                    continue;
                
                char buffer[4096];
                int bytes = recv(client_fd, buffer, sizeof(buffer)-1, 0);

                if (bytes < 0)
                {
                    close(client_fd);
                    continue;
                }

                buffer[bytes] = '\0';
                std::cout <<" Server received "<<bytes<<" bytes"<<std::endl;

                std::string response;
                if (std::string_view(buffer).find("HTTP") != std::string_view::npos)
                {
                    response = handleHttpRequest(buffer);
                }else{
                    response = ""; // impliment for other api's
                }

                send(client_fd, response.c_str(), response.size(), 0);
                std::cout<<"Sent to client "<<response.substr(0, 10)<<"..."<<std::endl;
                
                close(client_fd);
            }
            

        }
};

int main()
{
    try{
        Server srv(8080);
        srv.run();
    }catch (const std::exception& e){
        std::cerr << "Server init failed: "<<e.what() <<std::endl;
    }
}