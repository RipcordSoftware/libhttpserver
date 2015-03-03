#ifndef RS_LIBHTTPSERVER_TYPES_H
#define	RS_LIBHTTPSERVER_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

namespace rs {
namespace httpserver {

class HttpServer;
typedef boost::shared_ptr<HttpServer> server_ptr;
    
class Service;
typedef boost::shared_ptr<Service> service_ptr;

class HeaderBuffer;
typedef boost::shared_ptr<HeaderBuffer> header_buffer_ptr;

class Socket;
typedef boost::shared_ptr<Socket> socket_ptr;

class RequestHeaders;
typedef boost::shared_ptr<RequestHeaders> request_headers_ptr;

class Request;
typedef boost::shared_ptr<Request> request_ptr;

class Response;
typedef boost::shared_ptr<Response> response_ptr;

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> asio_socket_ptr;

}}

#endif	/* RS_LIBHTTPSERVER_TYPES_H */