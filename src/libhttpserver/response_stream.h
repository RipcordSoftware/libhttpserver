#ifndef RS_LIBHTTPSERVER_RESPONSE_STREAM_H
#define	RS_LIBHTTPSERVER_RESPONSE_STREAM_H

#include "types.h"
#include "stream.h"
#include "exceptions.h"
#include "socket.h"

namespace rs {
namespace httpserver {

class ResponseStream final : public Stream {
public:
    ResponseStream(socket_ptr socket) : socket_(socket) {}
    
    virtual void Flush() override;
    
    virtual int Read(Stream::byte* buffer, int offset, int count, bool peek = false) override {
        throw InvalidStreamOperationException();
    }
    
    virtual int Write(const Stream::byte* buffer, int offset, int count) override;
    
    virtual long getPosition() override {
        return position_;
    }
    
    virtual long getLength() override {
        return length_;
    }
    
private:
    socket_ptr socket_;
    long position_;
    long length_;
};

}}

#endif	/* RS_LIBHTTPSERVER_RESPONSE_STREAM_H */

