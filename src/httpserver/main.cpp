#include <sstream>

#include <boost/chrono.hpp>

#include "../libhttpserver/libhttpserver.h"

int main() {
    
    // create the server object
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024);
    
    // create a router
    auto router = rs::httpserver::RequestRouter();
    
    // if the client asks for / then redirect
    router.Add("GET", "/", [](rs::httpserver::request_ptr, const rs::httpserver::RequestRouter::CallbackArgs&, rs::httpserver::response_ptr response) {
        response->Redirect("/index.html");
        return true;
    });
    
    // if the client asks for /image= then respond with the image if we find it
    router.Add("GET", R"(/image=(?<filename>[0-9a-zA-z_\-]+\.(jpg|png)))", [](rs::httpserver::request_ptr request, const rs::httpserver::RequestRouter::CallbackArgs& args, rs::httpserver::response_ptr response) {
        auto filename = args.find("filename");
        std::string uri("www/"); uri += filename->second;
        rs::httpserver::FileStream stream(uri);
        if (stream) {
            auto contentType = rs::httpserver::MimeTypes::GetExtensionType(uri);
            response->setContentType(contentType.get()).Send(stream);
        }
        return true;
    });
    
    // if the client asks for /echo then respond with the client data
    auto echoHandler = [](rs::httpserver::request_ptr request, const rs::httpserver::RequestRouter::CallbackArgs&, rs::httpserver::response_ptr response) {
        if (request->HasBody()) {
            auto& requestStream = request->getRequestStream();
            auto contentType = request->getContentType();
            response->setContentType(contentType).Send(requestStream);
            return true;
        } else {
            return false;
        }
    };
    router.Add("POST", "/echo", echoHandler);
    router.Add("PUT", "/echo", echoHandler);
    
    // if the client asks for /time then return the time in ns since 1970
    router.Add("GET", "/time", [](rs::httpserver::request_ptr, const rs::httpserver::RequestRouter::CallbackArgs&, rs::httpserver::response_ptr response) {
        std::stringstream stream;
        stream << "<html><body>The current time is: " << boost::chrono::system_clock::now() << "</body></html>";
        response->setContentType("text/html").Send(stream);
        return true;
    });
    
    // if the client asks for /lorem then return some handy text
    router.Add("GET", "/lorem", [](rs::httpserver::request_ptr, const rs::httpserver::RequestRouter::CallbackArgs&, rs::httpserver::response_ptr response) {        
        auto& stream = response->setContentType("text/html").getResponseStream();
        char lorem[] = "<html><body>Bacon ipsum dolor amet flank corned beef pork chop andouille venison turkey chuck. Kevin t-bone venison flank kielbasa short ribs.</body></html>";
        stream.Write(reinterpret_cast<rs::httpserver::Stream::byte*>(lorem), 0, sizeof(lorem));
        stream.Flush();
        return true;
    });
    
    router.Add("GET", "/multipart", [](rs::httpserver::request_ptr, const rs::httpserver::RequestRouter::CallbackArgs&, rs::httpserver::response_ptr response) {
        std::string testTxt = "hello world";
        auto& stream = response->getMultiResponseStream();
        stream.EmitPart("text/plain", "test.txt", testTxt.size());
        rs::httpserver::Stream::Write(stream, testTxt);
        stream.Flush();
        
        return true;
    });
    
    // the default handler if all else fails
    auto defaultHandler = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request, rs::httpserver::response_ptr response) {
        auto uri = request->getUri();
        auto contentType = rs::httpserver::MimeTypes::GetExtensionType(uri);
        if (contentType) {
            uri = "www" + uri;

            rs::httpserver::FileStream stream(uri);

            // if the file exists then stream will be true
            if (stream) {
                // get the modified time of the file
                auto lastModifiedTime = stream.getLastModifiedTime();

                // assuming we have the modified time (v likely) then we can use etag/if-none-match for client-side caching
                if (lastModifiedTime) {
                    if (request->IsHttp10()) {
                        auto requestLastModifiedTime = request->getIfModifiedSince();
                        auto formattedLastModifiedTime = rs::httpserver::Response::FormatLastModifiedTime(lastModifiedTime.get());

                        if (requestLastModifiedTime.length() > 0 && requestLastModifiedTime == formattedLastModifiedTime) {
                            // the client already has the file
                            response->setStatusCode(304).setStatusDescription("Not Modified").Send();
                        } else {
                            // the client doesn't have the file, send the last modified
                            response->setLastModified(formattedLastModifiedTime);
                        }
                    } else {
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
                } 

                // if we haven't responded yet then send the stream
                if (!response->HasResponded()) {
                    response->setContentType(contentType.get()).Send(stream);
                }
            }
        }
    };    

    server->Start(router, defaultHandler);
    
    return 0;
}