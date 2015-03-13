#ifndef RS_LIBHTTPSERVER_REQUEST_STREAM_H
#define	RS_LIBHTTPSERVER_REQUEST_STREAM_H

#include <boost/noncopyable.hpp>

#include "stream.h"
#include "exceptions.h"
#include "socket.h"
#include "header_buffer.h"

namespace rs {
namespace httpserver {

class RequestStream final : public Stream, private boost::noncopyable {
public:
    RequestStream(socket_ptr socket, HeaderBuffer& headerBuffer) : 
        socket_(socket), position_(0), length_(0), headerBuffer_(headerBuffer),
        explictLength_(false) {}
    
    virtual void Flush() override {};
    
    virtual int Read(Stream::byte* buffer, int offset, int count, bool peek = false) override;
    
    virtual int Write(const Stream::byte* buffer, int offset, int count) override {
        throw InvalidStreamOperationException();
    }
    
    virtual long getPosition() override {
        return position_;
    }
    
    virtual long getLength() override {
        return length_;
    }
    
    void setLength(long length) {
        if (length < position_) {
            throw InvalidStreamOperationException();
        }
        
        length_ = length;
        explictLength_ = true;
    }

private:
    
    socket_ptr socket_;
    long position_;
    long length_;
    bool explictLength_;
    
    HeaderBuffer& headerBuffer_;

};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_STREAM_H */

