#ifndef RS_LIBHTTPSERVER_MULTIPART_RESPONSE_STREAM_H
#define RS_LIBHTTPSERVER_MULTIPART_RESPONSE_STREAM_H

#include "stream.h"
#include "response_headers.h"

namespace rs {
namespace httpserver {

class MultipartResponseStream final : public Stream {
public:
    MultipartResponseStream(Stream& stream);
    MultipartResponseStream(const MultipartResponseStream&) = delete;
    
    virtual void Flush() override;
    
    virtual int Read(Stream::byte* buffer, int offset, int count, bool peek = false) override;
    
    virtual int Write(const Stream::byte* buffer, int offset, int count) override;
    
    virtual long getPosition() override;
    
    virtual long getLength() override;
    
    void EmitPart(const char* contentType, const char* filename = nullptr, std::int64_t contentLength = -1);
    
    unsigned getPartCount() { return partCount_; }
    
    static const char* boundary;
    
private:   
    
    static const char* boundaryStart;
    static const char* boundaryEnd;
    static const unsigned boundaryEndLength;
    
    Stream& stream_;
    unsigned partCount_{0};
};

}}

#endif	/* RS_LIBHTTPSERVER_MULTIPART_RESPONSE_STREAM_H */

