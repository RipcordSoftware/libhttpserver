#include <algorithm>
#include <boost/bind.hpp>

#include "header_buffer.h"
#include "socket.h"

std::size_t rs::httpserver::HeaderBuffer::Receive(socket_ptr socket) {
    return Receive(boost::bind(&Socket::Receive, socket, _1, _2, _3));
}

std::size_t rs::httpserver::HeaderBuffer::Receive(boost::function<std::size_t(Stream::byte* buffer, int length, bool peek)> func) {
    auto bytes = func(reinterpret_cast<Stream::byte*>(&data_[0]) + dataLength_, data_.size() - dataLength_, false);
    if (bytes > 0) {
        dataLength_ += bytes;
    }
    
    return bytes;
}

std::size_t rs::httpserver::HeaderBuffer::Receive(socket_ptr socket, int timeout) {
    return Receive(boost::bind(&Socket::Receive, socket, _1, _2, _3, _4), timeout);
}

std::size_t rs::httpserver::HeaderBuffer::Receive(boost::function<std::size_t(int timeout, Stream::byte* buffer, int length, bool peek)> func, int timeout) {
    auto bytes = func(timeout, reinterpret_cast<Stream::byte*>(&data_[0]) + dataLength_, data_.size() - dataLength_, false);
    if (bytes > 0) {
        dataLength_ += bytes;
    }
    
    return bytes;
}

int rs::httpserver::HeaderBuffer::Copy(value_type* buffer, int count, bool peek) {
    auto length = std::min(dataLength_ - position_, count);
    auto start = cbegin() + position_;
    std::copy(start, start + length, buffer);

    if (!peek) {
        position_ += length;
    }

    return length;
}