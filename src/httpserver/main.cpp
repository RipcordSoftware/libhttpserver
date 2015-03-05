#include "../libhttpserver/libhttpserver.h"

int main() {
    
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024);
    
    auto func = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request, rs::httpserver::response_ptr response) {
        rs::httpserver::FileStream stream("www/test.html");
        if (stream) {
            response->setContentType("text/html").setContentLength(stream.getLength()).Send(stream);
            return true;
        } else {
            return false;
        }
    };    

    server->Start(func);
    
    return 0;
}