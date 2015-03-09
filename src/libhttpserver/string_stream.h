#ifndef RS_LIBHTTPSERVER_STRING_STREAM_H
#define	RS_LIBHTTPSERVER_STRING_STREAM_H

#include <algorithm>

#include <boost/noncopyable.hpp>

#include "stream.h"
#include "exceptions.h"

namespace rs {
namespace httpserver {
    
class StringStream final : public Stream, private boost::noncopyable {
public:
    StringStream(const std::string& data) : data_(data), position_(0) {}
    
    virtual void Flush() override {};
    
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override {       
        int bytes = 0;
        
        if (position_ < data_.length()) {
            auto data = reinterpret_cast<const byte*>(data_.c_str());
            if (data != nullptr) {
                int length = data_.length();
                bytes = std::min(count, length - position_);
                std::copy(data + position_, data + position_ + bytes, buffer + offset);

                if (!peek) {
                    position_ += bytes;
                }
            }
        }
        
        return bytes;
    }
    
    virtual int Write(const byte* buffer, int offset, int count) override {
        throw InvalidStreamOperationException();
    }
    
    virtual long getPosition() override { return position_; }
    
    virtual long getLength() override { return data_.length(); }
    
    void AppendData(const std::string& data) {
        data_ += data;
    }
    
private:
    std::string data_;
    int position_;
};

}}

#endif	/* RS_LIBHTTPSERVER_STRING_STREAM_H */

