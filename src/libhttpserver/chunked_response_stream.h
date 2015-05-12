#ifndef RS_LIBHTTPSERVER_CHUNKED_RESPONSE_STREAM_H
#define	RS_LIBHTTPSERVER_CHUNKED_RESPONSE_STREAM_H

#include "stream.h"
#include "exceptions.h"
#include "config.h"

#include <vector>

namespace rs {
namespace httpserver {

class ChunkedResponseStream final : public Stream {
public:
    ChunkedResponseStream(Stream& stream) : stream_(stream), position_(0), length_(0),
        maxBlockSizeHeader_(GetHeader(Config::MaxResponseChunkSize)) {}        
    
    virtual void Flush() override;

    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override {
        throw InvalidStreamOperationException();
    }
    
    virtual int Write(const byte* buffer, int offset, int count) override;
    
    virtual long getPosition() override { return position_; }
    
    virtual long getLength() override { return length_; }
    
private:
    static std::vector<Stream::byte> GetHeader(int blockSize);
    
    Stream& stream_;
    long position_;
    long length_;
    
    const std::vector<Stream::byte> maxBlockSizeHeader_;
    static const Stream::byte endOfBlocks_[5];
    static const Stream::byte endOfLine_[2];
  
};

}}

#endif	/* RS_LIBHTTPSERVER_CHUNKED_RESPONSE_STREAM_H */

