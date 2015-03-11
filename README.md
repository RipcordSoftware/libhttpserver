[![Build Status](https://travis-ci.org/RipcordSoftware/libhttpserver.svg?branch=master)](https://travis-ci.org/RipcordSoftware/libhttpserver)

# libhttpserver
An HTTP web server implemented in C++ 11 and based on Boost::Asio.

Features:
* Handles HTTP 1.0 and 1.1 clients
* Supports chunked POST/PUT requests
* Supports chunked responses
* Support GZIP responses
* Low memory overhead streaming response API with helpers for strings and files

## Examples
The simplist possible web server:
```c++
#include "libhttpserver.h"
using rs::httpserver;

int main() {
  auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 1080);
  auto func = [](socket_ptr socket, request_ptr request, response_ptr response) {
    response->setContentType("text/html").Send("<html><body><h1>Hello from libhttpserver</h1></body></html>");
  };
  server->Start(func);
  return 0;
}
```
Respond from the filesystem:
```c++
#include "libhttpserver.h"
using rs::httpserver;

int main() {
  // the server will listen on all IPs on port 1080
  auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 1080);
  
  // a lambda function which handles the request
  auto func = [](socket_ptr socket, request_ptr request, response_ptr response) {
    // get the request uri
    auto uri = request->getUri();
    
    if (uri == "/") {
      // the uri was just /, redirect to /index.html
      response->setLocation("/index.html").setStatusCode(302).Send();
    } else {
      // use the uri file extension to determine the content type
      auto contentType = rs::httpserver::MimeTypes::GetType(uri);
      
      // we only respond if we got a content type
      if (contentType) {
        // the content files are in the www sub-directory
        uri = "www" + uri;
        
        // open a stream on the file
        rs::httpserver::FileStream stream(uri);
        if (stream) {
          // respond with the contents of the file
          response->setContentType(contentType.get()).Send(stream);
        }
    }
  };
  
  // starts the server and blocks
  server->Start(func);
  return 0;
}
```

## Building
You will need:
* GCC 4.8 or higher
* GNU Make
* Boost 1.53 or higher
* ZLib 1.2.7

To build the binaries:
```
 $ make
```

To build and run the tests:
```
 $ make test
```
