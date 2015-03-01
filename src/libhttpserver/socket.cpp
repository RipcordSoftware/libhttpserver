#include <boost/bind.hpp>

#include "socket.h"

rs::httpserver::socket_ptr rs::httpserver::Socket::Create(server_ptr server, asio_socket_ptr asio_socket) {
    auto socket = new Socket(server, asio_socket);
    return socket_ptr(socket);
}

std::size_t rs::httpserver::Socket::Receive(buffer& b) {
    if (socket_->available() <= 0 ) {
        setDefaultReceiveTimeout();
    }
    
    return socket_->receive(boost::asio::mutable_buffers_1(static_cast<void*>(&b[0]), b.size()));
}

std::size_t rs::httpserver::Socket::Receive(int timeout, buffer& b) {
    bool timed_out = false;
    
    if (socket_->available() <= 0 ) {
        setCustomReceiveTimeout(timeout);        
        
        char canary;
        timed_out = ::recv(socket_->native_handle(), &canary, 1, MSG_PEEK) <= 0;    
    }
    
    return !timed_out ? socket_->receive(boost::asio::mutable_buffers_1(static_cast<void*>(&b[0]), b.size())) : 0;
}

int rs::httpserver::Socket::getReceiveTimeout(asio_socket_ptr socket) {
    struct ::timeval tv;
    socklen_t tv_length = sizeof(tv);
    if (::getsockopt(socket->native_handle(), SOL_SOCKET, SO_RCVTIMEO, &tv, &tv_length) == 0) {
        return tv.tv_sec;
    } else {
        return -1;
    }
}

bool rs::httpserver::Socket::setReceiveTimeout(asio_socket_ptr socket, int seconds) {
    struct ::timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;
    return ::setsockopt(socket->native_handle(), SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == 0;
}

void rs::httpserver::Socket::setDefaultReceiveTimeout() {
    if (defaultReceiveTimeout >= 0 && defaultReceiveTimeout != currentReceiveTimeout) {
        setReceiveTimeout(getAsioSocket(), defaultReceiveTimeout);
        currentReceiveTimeout = defaultReceiveTimeout;
    }
}

void rs::httpserver::Socket::setCustomReceiveTimeout(int seconds) {
    if (defaultReceiveTimeout <= 0) {
        defaultReceiveTimeout = getReceiveTimeout(getAsioSocket());
    }
    
    if (currentReceiveTimeout != seconds) {                
        setReceiveTimeout(getAsioSocket(), seconds);
        currentReceiveTimeout = seconds;
    }
}
