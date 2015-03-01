#include <iostream>

#include "../libhttpserver/libhttpserver.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024, 8);
    
    auto func = [](rs::httpserver::socket_ptr socket) {
        rs::httpserver::Socket::buffer b(1024);
        auto bytes = socket->Receive(5, b);

        std::cout << "got bytes: " << bytes << std::endl;

        auto remote = socket->getRemoteEndpoint();

        stringstream html;
        html << "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body>hello to " << remote.address().to_string() << ":" << remote.port() << "</body></html>";

        socket->Send(html.str());
        
        return true;
    };

    server->Start(func, [](rs::httpserver::socket_ptr){ return true; });    
    
    return 0;
}