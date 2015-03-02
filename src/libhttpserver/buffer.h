#ifndef RS_LIBHTTPSERVER_BUFFER_H
#define	RS_LIBHTTPSERVER_BUFFER_H

#include <vector>

#include <boost/noncopyable.hpp>

#include "types.h"
#include "exceptions.h"

namespace rs {
namespace httpserver {

class Buffer final : boost::noncopyable {
public:
    Buffer(int size) : data_(size), dataLength_(0) {}
    
    int getLength() const {
        return data_.size();
    }
        
    int getDataLength() const {
        return dataLength_;
    }
    
    void setDataLength(int length) {
        if (length >= data_.size()) {
            throw InvalidBufferDataLengthException();
        }
        
        dataLength_ = length;        
    }
    
    unsigned char* getData() {
        return &data_[0];
    }
    
    bool IsFull () {
        return dataLength_ == data_.size();
    }
    
private:        
    std::vector<unsigned char> data_;
    int dataLength_;
};

}}

#endif	/* RS_LIBHTTPSERVER_BUFFER_H */

