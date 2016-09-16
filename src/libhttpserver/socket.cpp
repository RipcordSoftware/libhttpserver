#include <boost/bind.hpp>

#include "socket.h"
#include "socket_timeval_option.h"

rs::httpserver::socket_ptr rs::httpserver::Socket::Create(server_ptr server, asio_socket_ptr asio_socket) {
    auto socket = new Socket(server, asio_socket);
    
#if defined (__linux__)
    socket->setDefaultReceiveTimeout();
#endif
    
    return socket_ptr(socket);
}

std::size_t rs::httpserver::Socket::Receive(byte* buffer, int length, bool peek) {
    auto bytes = socket_->receive(boost::asio::mutable_buffers_1(buffer, length), peek ? boost::asio::socket_base::message_peek : 0);    
    totalBytesReceived_ += bytes > 0 ? bytes : 0;
    return bytes;
}

std::size_t rs::httpserver::Socket::Receive(int timeout, byte* buffer, int length, bool peek) {
    auto bytes = 0;
    
    if (Peek(timeout)) {
        bytes = socket_->receive(boost::asio::mutable_buffers_1(buffer, length), peek ? boost::asio::socket_base::message_peek : 0);
        totalBytesReceived_ += bytes > 0 ? bytes : 0;
    }
    
    return bytes;
}

int rs::httpserver::Socket::getReceiveTimeout(asio_socket_ptr socket) {
    int seconds = -1;
    
    SocketTimevalOption<SOL_SOCKET, SO_RCVTIMEO> timeout;
    boost::system::error_code ec;
    socket->get_option(timeout, ec);
    if (ec.value() == boost::system::errc::success) {
        seconds = timeout.seconds();
    }
    
    return seconds;
}

bool rs::httpserver::Socket::setReceiveTimeout(asio_socket_ptr socket, int seconds) {
    SocketTimevalOption<SOL_SOCKET, SO_RCVTIMEO> timeout{seconds};
    boost::system::error_code ec;
    socket->set_option(timeout, ec);
    return ec.value() == boost::system::errc::success;
}

void rs::httpserver::Socket::setDefaultReceiveTimeout() {
    if (defaultReceiveTimeout_ >= 0 && defaultReceiveTimeout_ != currentReceiveTimeout_) {
        setReceiveTimeout(getAsioSocket(), defaultReceiveTimeout_);
        currentReceiveTimeout_ = defaultReceiveTimeout_;
    }
}

void rs::httpserver::Socket::setCustomReceiveTimeout(int seconds) {
    if (defaultReceiveTimeout_ <= 0) {
        defaultReceiveTimeout_ = getReceiveTimeout(getAsioSocket());
    }
    
    if (currentReceiveTimeout_ != seconds) {                
        setReceiveTimeout(getAsioSocket(), seconds);
        currentReceiveTimeout_ = seconds;
    }
}

#if defined (__linux__)
bool rs::httpserver::Socket::Peek(int timeout) {
    auto available = socket_->available();
    
    if (available <= 0 ) {
        setCustomReceiveTimeout(timeout);
        
        char canary;
        available = ::recv(socket_->native_handle(), &canary, 1, MSG_PEEK);
    }
    
    return available > 0;
}
#else
bool rs::httpserver::Socket::Peek(int timeout) {
    auto available = socket_->available();
    
    if (available <= 0) {
        struct pollfd fd{.fd=socket_->native_handle(), .events=POLLRDNORM, .revents=0};
        struct pollfd fds[1] = { fd };
        available = ::poll(fds, 1, timeout * 1000);
    }
    
    return available > 0;
}
#endif
