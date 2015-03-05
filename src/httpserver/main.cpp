#include "../libhttpserver/libhttpserver.h"

int main() {
    
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024);
    
    auto func = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request, rs::httpserver::response_ptr response) {
        rs::httpserver::FileStream stream("www/rfc2616.txt");
        if (stream) {
            response->setContentType("text/plain").Send(stream);
        }       
    };    

    server->Start(func);
    
    return 0;
}