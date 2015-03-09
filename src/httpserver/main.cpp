#include "../libhttpserver/libhttpserver.h"

int main() {
    
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024);
    
    auto func = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request, rs::httpserver::response_ptr response) {
        auto uri = request->getUri();
        if (uri == "/") {
            rs::httpserver::FileStream stream("www/index.html");
            if (stream) {
                response->setContentType("text/html", true).Send(stream);
            }       
        } else {
            auto contentType = rs::httpserver::MimeTypes::GetType(uri);
            if (contentType) {                            
                uri = "www" + uri;
            
                rs::httpserver::FileStream stream(uri);
                if (stream) {
                    response->setContentType(contentType.get()).Send(stream);
                }
            }
        }
    };    

    server->Start(func);
    
    return 0;
}