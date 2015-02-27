#include "service.h"

void rs::httpwebserver::Service::Listen(const std::string& host, int port, listen_callback func) {
    auto addr = boost::asio::ip::address::from_string(host);
    boost::asio::ip::tcp::endpoint ep(addr, port);
    asio_acceptor_ptr acceptor(new boost::asio::ip::tcp::acceptor(*service_, ep));
    
    auto socket = Socket::Create(shared_from_this(), acceptor);    
    Service::StartAccept(socket, func);
}

void rs::httpwebserver::Service::StartAccept(socket_ptr socket, listen_callback func) {
    socket->getAsioAcceptor()->async_accept(*socket->getAsioSocket(),
            boost::bind((void (*)(socket_ptr, listen_callback, const boost::system::error_code&))&Service::HandleAccept, 
            socket, func, boost::asio::placeholders::error));
}

void rs::httpwebserver::Service::HandleAccept(socket_ptr socket, listen_callback func, const boost::system::error_code& error) {
    socket->getAsioAcceptor()->async_accept(*socket->getAsioSocket(), boost::bind(func, socket, error));
    
    auto new_socket = Socket::Create(socket->getService(), socket->getAsioAcceptor());    
    Service::StartAccept(new_socket, func);
}