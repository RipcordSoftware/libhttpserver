#include <iostream>

#include "../libhttpserver/libhttpserver.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024, 8);
    
    auto func = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request) {
        auto remote = socket->getRemoteEndpoint();

        stringstream html;
        html << "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body>hello to " << 
            remote.address().to_string() << ":" << remote.port() <<
            " from " << request->getHeaders()->getHost() << 
            " at uri " << request->getHeaders()->getUri() <<
            "</body></html>";

        socket->Send(html.str());
        
        return true;
    };

    server->Start(func);
    
    return 0;
}