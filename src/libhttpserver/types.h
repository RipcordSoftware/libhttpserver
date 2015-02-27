#ifndef RS_LIBHTTPSERVER_TYPES_H
#define	RS_LIBHTTPSERVER_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

namespace rs {
namespace httpwebserver {

class Service;
typedef boost::shared_ptr<Service> service_ptr;

class Socket;
typedef boost::shared_ptr<Socket> socket_ptr;

typedef boost::shared_ptr<boost::asio::io_service> asio_io_service_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> asio_socket_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::acceptor> asio_acceptor_ptr;

}}

#endif	/* RS_LIBHTTPSERVER_TYPES_H */