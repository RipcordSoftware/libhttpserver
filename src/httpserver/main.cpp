#include <iostream>

#include "../libhttpserver/libhttpserver.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    auto service = rs::httpwebserver::Service::Create(8);
    
    auto func = [](rs::httpwebserver::socket_ptr socket, const boost::system::error_code & err) {
        if (!!err) {
            cout << "Error: " << err.message() << endl;
        } else {
            rs::httpwebserver::Socket::buffer b(1024);
            auto bytes = socket->Receive(5, b);
            
            std::cout << "got bytes: " << bytes << std::endl;
            
            auto remote = socket->getRemoteEndpoint();
            
            stringstream html;
            html << "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body>hello to " << remote.address().to_string() << ":" << remote.port() << "</body></html>";
            
            socket->Send(html.str());
        }
    };

    service->Listen("0.0.0.0", 10024, func);
    
    service->Run();
    
    return 0;
}