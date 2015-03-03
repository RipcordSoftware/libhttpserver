#include <algorithm>

#include "header_buffer.h"
#include "socket.h"
#include "stream.h"

std::size_t rs::httpserver::HeaderBuffer::Receive(rs::httpserver::socket_ptr socket) {
    auto bytes = socket->Receive(reinterpret_cast<rs::httpserver::Stream::byte*>(&data_[0]) + dataLength_, data_.size() - dataLength_);
    if (bytes > 0) {
        dataLength_ += bytes;
    }
    
    return bytes;
}

std::size_t rs::httpserver::HeaderBuffer::Receive(rs::httpserver::socket_ptr socket, int timeout) {
    auto bytes = socket->Receive(timeout, reinterpret_cast<rs::httpserver::Stream::byte*>(&data_[0]) + dataLength_, data_.size() - dataLength_);
    if (bytes > 0) {
        dataLength_ += bytes;
    }
    
    return bytes;
}

int rs::httpserver::HeaderBuffer::Copy(value_type* buffer, int count) {
    auto length = std::min(dataLength_ - position_, count);
    auto start = cbegin() + position_;
    std::copy(start, start + length, buffer);
    position_ += length;
    return length;
}