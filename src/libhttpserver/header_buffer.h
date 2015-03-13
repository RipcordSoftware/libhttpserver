#ifndef RS_LIBHTTPSERVER_HEADER_BUFFER_H
#define	RS_LIBHTTPSERVER_HEADER_BUFFER_H

#include <vector>

#include <boost/noncopyable.hpp>

#include "types.h"
#include "exceptions.h"

namespace rs {
namespace httpserver {

class HeaderBuffer final : private boost::noncopyable {
public:
    typedef char value_type;
    
    HeaderBuffer(int size) : data_(size), dataLength_(0), position_(0) {}
    
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
    
    std::size_t Receive(rs::httpserver::socket_ptr socket);
    std::size_t Receive(rs::httpserver::socket_ptr socket, int timeout);
    
    int Copy(value_type* buffer, int count, bool peek = false);
    
private:        
    std::vector<value_type> data_;
    int dataLength_;
    int position_;
};

}}

#endif	/* RS_LIBHTTPSERVER_HEADER_BUFFER_H */

