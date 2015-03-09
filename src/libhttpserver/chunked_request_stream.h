#ifndef RS_LIBHTTPSERVER_CHUNKED_REQUEST_STREAM_H
#define	RS_LIBHTTPSERVER_CHUNKED_REQUEST_STREAM_H

#include <boost/noncopyable.hpp>

#include "stream.h"
#include "exceptions.h"
#include "config.h"

namespace rs {
namespace httpserver {

class ChunkedRequestStream final : public Stream, private boost::noncopyable {
public:
    ChunkedRequestStream(Stream& stream) : stream_(stream), position_(0), length_(0),
        chunkLength_(0), chunkPosition_(0) {}
    
    virtual void Flush() override {}
    
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override;
    
    virtual int Write(const byte* buffer, int offset, int count) override {
        throw InvalidStreamOperationException();
    }
    
    virtual long getPosition() override { return position_; }
    
    virtual long getLength() override { return length_;  }

private:
    void ReadHeader();
    static bool GetChunkSize(const byte* buffer, const int bufferLength, int& chunkLength, int& headerLength);
    
    Stream& stream_;
    long position_;
    long length_;

    int chunkLength_;
    int chunkPosition_;
    
    static const byte endOfLine_[2];
};

}}

#endif	/* RS_LIBHTTPSERVER_CHUNKED_REQUEST_STREAM_H */

