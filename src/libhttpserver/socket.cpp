#include "socket.h"
#include "service.h"

rs::httpwebserver::socket_ptr rs::httpwebserver::Socket::Create(service_ptr service, std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor) {
    auto socket = new Socket(service, boost::shared_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket(*service)), acceptor);
    return socket_ptr(socket);
}

void rs::httpwebserver::Socket::Listen(const std::string& host, int port, boost::function<void (socket_ptr, const boost::system::error_code &)> func) {
    auto addr = boost::asio::ip::address::from_string(host);
    boost::asio::ip::tcp::endpoint ep(addr, port);
    acceptor_.reset(new boost::asio::ip::tcp::acceptor(*service_, ep));
    
    StartAccept(func);
}

void rs::httpwebserver::Socket::StartAccept(boost::function<void (socket_ptr, const boost::system::error_code &)> func) {
    acceptor_->async_accept(*socket_, boost::bind((void (*)(socket_ptr, boost::function<void (socket_ptr, const boost::system::error_code &)>, const boost::system::error_code&))&Socket::HandleAccept, shared_from_this(), func, boost::asio::placeholders::error));
}

void rs::httpwebserver::Socket::HandleAccept(socket_ptr socket, boost::function<void (socket_ptr, const boost::system::error_code &)> func, const boost::system::error_code& error) {
    socket->acceptor_->async_accept(*socket->socket_, boost::bind(func, socket, error));
    
    auto new_socket = Create(socket->service_, socket->acceptor_);    
    new_socket->StartAccept(func);
}