[![Build Status](https://travis-ci.org/RipcordSoftware/libhttpserver.svg?branch=master)](https://travis-ci.org/RipcordSoftware/libhttpserver)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/libhttpserver/badge.svg)](https://coveralls.io/r/RipcordSoftware/libhttpserver)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

# libhttpserver
An HTTP web server implemented in C++ 11 and based on Boost::Asio.

Features:
* Handles HTTP 1.0 and 1.1 clients
* Handles chunked POST/PUT requests
* Supports chunked responses
* Supports GZIP responses
* Low memory overhead streaming response API with helpers for strings and files
* Utilizes HTTP keep-alive up to a configured request limit

## Build Status

| OS           | Architecture       | Status                       |
|--------------|--------------------|------------------------------|
| Debian 8.6   | i386               | [![debian-8.6-i386](https://jenkins.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-debian-i386-8.6)](https://jenkins.ripcordsoftware.com/job/libhttpserver-debian-i386-8.6/) |
| Debian 8.6   | amd64              | [![debian-8.6-amd64](https://jenkins.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-debian-8.6)](https://jenkins.ripcordsoftware.com/job/libhttpserver-debian-8.6/) |
| Ubuntu 14.04 | amd64              | [![ubutu-14.04-amd64](https://jenkins.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-ubuntu-14.04)](https://jenkins.ripcordsoftware.com/job/libhttpserver-ubuntu-14.04/) |
| Ubuntu 16.04 | amd64              | [![ubuntu-16.04-amd64](https://jenkins.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-ubuntu-16.04)](https://jenkins.ripcordsoftware.com/job/libhttpserver-ubuntu-16.04/) |
| CentOS 6.8   | amd64              | [![centos-6.8-amd64](https://jenkins.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-centos-6.8)](https://jenkins.ripcordsoftware.com/job/libhttpserver-centos-6.8/) |
| CentOS 7.3   | amd64              | [![centos-7.3-amd64](https://jenkins.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-centos-7.3)](https://jenkins.ripcordsoftware.com/job/libhttpserver-centos-7.3/) |
| Fedora 25    | amd64              | [![fedora-25-amd64](https://jenkins.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-fedora-25)](https://jenkins.ripcordsoftware.com/job/libhttpserver-fedora-25/) |
| FreeBSD 11   | amd64              | [![freebsd-11-amd64](https://jenkins-bsd.ripcordsoftware.com/buildStatus/icon?job=libhttpserver-freebsd-11)](https://jenkins-bsd.ripcordsoftware.com/job/libhttpserver-freebsd-11/) |

## Examples
The simplist possible web server:
```c++
#include "libhttpserver.h"
using rs::httpserver;

int main() {
  auto server = HttpServer::Create("0.0.0.0", 1080);
  auto func = [](socket_ptr socket, request_ptr request, response_ptr response) {
    response->setContentType("text/html").Send("<html><body><h1>Hello from libhttpserver</h1></body></html>");
  };
  server->Start(func);
}
```
Respond from the filesystem:
```c++
#include "libhttpserver.h"
using rs::httpserver;

int main() {
  // the server will listen on all IPs on port 1080
  auto server = HttpServer::Create("0.0.0.0", 1080);
  
  // a lambda function which handles the request
  auto func = [](socket_ptr socket, request_ptr request, response_ptr response) {
    // get the request uri
    auto uri = request->getUri();
    
    if (uri == "/") {
      // the uri was just /, redirect to /index.html
      response->Redirect("/index.html");
    } else {
      // use the uri file extension to determine the content type
      auto contentType = MimeTypes::GetType(uri);
      
      // we only respond if we got a content type
      if (contentType) {
        // the content files are in the www sub-directory
        uri = "www" + uri;
        
        // open a stream on the file
        FileStream stream(uri);
        if (stream) {
          // respond with the contents of the file
          response->setContentType(contentType.get()).Send(stream);
        }
    }
  };
  
  // starts the server and blocks
  server->Start(func);
}
```
The example above assumes the web content is in the sub-directory `www`. If the content type could not be found or the file does not exist then the server will respond with a `404 Not Found`.

You can extend the Content/MIME type mapping as follows: 
```c++
rs::httpserver::MimeTypes::AddType(".bz2", "application/x-bzip2", false);
```

See `src/httpserver/main.cpp` for a working file based web server impl with last-modified/etag support.

## Building
You will need:
* GCC 4.8 or clang 3.5 or higher
* GNU Make
* Boost 1.53 or higher
* ZLib 1.2.7 or higher
* Doxygen (for the docs)

To build the binaries on Linux:
```
 $ make
```

To build and run the tests:
```
 $ make test
```

To build the documentation:
```
 $ make docs
```

On OSX or BSD add `CC=clang CXX=clang++` to the command line, e.g. `make CC=clang CXX=clang++`.

## Linking
Apart from including the `libhttpserver.h` you will need to configure your application to link against the following libraries:
* libhttpserver (!)
* boost_filesystem
* boost_thread
* boost_date_time
* boost_system
* zlib
* pthreads
