#ifndef RS_LIBHTTPSERVER_HEADER_BUFFER_H
#define	RS_LIBHTTPSERVER_HEADER_BUFFER_H

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

#include "types.h"
#include "exceptions.h"
#include "stream.h"

namespace rs {
namespace httpserver {

class HeaderBuffer final : private boost::noncopyable {
public:
    typedef char value_type;
    
    HeaderBuffer(int size = 4096) : data_(size), dataLength_(0), position_(0) {}
    
    int getLength() const {
        return data_.size();
    }
        
    int getDataLength() const {
        return dataLength_;
    }
    
    int getPosition() const {
        return position_;
    }
    
    void setDataLength(int length) {
        if (length >= data_.size()) {
            throw InvalidBufferDataLengthException();
        }
        
        dataLength_ = length;        
    }
    
    void setPosition(int pos) {
        if (pos > dataLength_) {
            throw InvalidBufferPositionException();
        }
        
        position_ = pos;
    }
    
    value_type* getData() {
        return &data_[0];
    }
    
    bool IsFull() {
        return dataLength_ == data_.size();
    }
    
    bool HasData() {
        return position_ < dataLength_;
    }
        
    const value_type* const cbegin() const {
        return &data_[0];
    }
    
    const value_type* const cend() const {
        return cbegin() + dataLength_;
    }
    
    void Reset() {
        dataLength_ = 0;
        position_ = 0;
    }
    
    std::size_t Receive(socket_ptr socket);
    std::size_t Receive(boost::function<std::size_t(Stream::byte* buffer, int length, bool peek)> func);
    
    std::size_t Receive(socket_ptr socket, int timeout);
    std::size_t Receive(boost::function<std::size_t(int timeout, Stream::byte* buffer, int length, bool peek)> func, int timeout);
    
    int Copy(value_type* buffer, int count, bool peek = false);
    
private:        
    std::vector<value_type> data_;
    int dataLength_;
    int position_;
};

}}

#endif	/* RS_LIBHTTPSERVER_HEADER_BUFFER_H */

