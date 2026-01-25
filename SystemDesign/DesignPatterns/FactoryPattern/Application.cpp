
#include "Factory.hpp"

class Application
{   
    std::unique_ptr<BackendCommunicator> serverInstance;
    Factory factory;
    public:

        Application( const std::string& type)
        {   
            
            serverInstance = factory.createBackendServer(type);
            serverInstance->connectServer("127.0.0.0", '8080');
        }

        void processData()
        {
            Packet pkt(12345, "Hello from Application Layer!");
            std::cout << "\n=== Sending Packet ===" << std::endl;
            
            Response resp = serverInstance->sendPostRequest(pkt);
            
            std::cout << "Response Status: " << resp.status << std::endl;
            std::cout << "Response Payload: " << resp.result << std::endl;
        }
};

int main()
{   
    std::cout << "\n=== HTTP Backend Demo ===" << std::endl;
    {
        Application app_http("http");
        app_http.processData();
    }
    return 0;
}