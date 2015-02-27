#include "socket.h"
#include "service.h"

rs::httpwebserver::socket_ptr rs::httpwebserver::Socket::Create(service_ptr service, asio_acceptor_ptr acceptor) {
    auto socket = new Socket(service, asio_socket_ptr(new boost::asio::ip::tcp::socket(*service)), acceptor);
    return socket_ptr(socket);
}