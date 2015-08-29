#include <boost/bind.hpp>

#include "socket.h"

rs::httpserver::socket_ptr rs::httpserver::Socket::Create(server_ptr server, asio_socket_ptr asio_socket) {
    auto socket = new Socket(server, asio_socket);
    return socket_ptr(socket);
}

std::size_t rs::httpserver::Socket::Receive(byte* buffer, int length, bool peek) {
    if (socket_->available() <= 0 ) {
        setDefaultReceiveTimeout();
    }
    
    auto bytes = socket_->receive(boost::asio::mutable_buffers_1(buffer, length), peek ? boost::asio::socket_base::message_peek : 0);    
    totalBytesReceived_ += bytes;
    return bytes;
}

std::size_t rs::httpserver::Socket::Receive(int timeout, byte* buffer, int length, bool peek) {
    bool timed_out = false;
    auto bytes = 0;
    
	// OSX doesn't seem to work with SO_RCVTIMEO in the same way as Linux
	// so don't bother with PEEK/timeout logic for the moment since this just
	// breaks the web server - this problem will be investigated and
	// fixed later
#if not defined (__APPLE__)	
    if (socket_->available() <= 0 ) {
        setCustomReceiveTimeout(timeout);        
        
        char canary;
        timed_out = ::recv(socket_->native_handle(), &canary, 1, MSG_PEEK) <= 0;    
    }
#endif
    
    if (!timed_out) {
        bytes = socket_->receive(boost::asio::mutable_buffers_1(buffer, length), peek ? boost::asio::socket_base::message_peek : 0);
    }
    
    totalBytesReceived_ += bytes;    
    
    return bytes;
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
