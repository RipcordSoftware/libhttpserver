#include "../libhttpserver/libhttpserver.h"

int main() {
    
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024);
    
    auto func = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request, rs::httpserver::response_ptr response) {
        auto uri = request->getUri();
        if (uri == "/") {
            response->setLocation("/index.html").setStatusCode(302).Send();
        } else {
            auto contentType = rs::httpserver::MimeTypes::GetType(uri);
            if (contentType) {
                uri = "www" + uri;
            
                rs::httpserver::FileStream stream(uri);
                
                // if the file exists then stream will be true
                if (stream) {
                    // get the modified time of the file
                    auto lastModifiedTime = stream.getLastModifiedTime();

                    // assuming we have the modified time (v likely) then we can use etag/if-none-match for client-side caching
                    if (lastModifiedTime) {
                        // we use the timestamp as the etag
                        auto etag = boost::lexical_cast<std::string>(lastModifiedTime.get());

                        // compare the etag with the value from the client
                        if (etag == request->getIfNoneMatch()) {
                            // the client already has the file
                            response->setStatusCode(304).setStatusDescription("Not Modified").Send();
                        } else {
                            // the client doesn't have the file, we need to return the etag
                            response->setETag(etag);
                        }
                    } 
                    
                    // if we haven't responded yet then send the stream
                    if (!response->HasResponded()) {
                        response->setContentType(contentType.get()).Send(stream);
                    }
                }
            }
        }
    };    

    server->Start(func);
    
    return 0;
}