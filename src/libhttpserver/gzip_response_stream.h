#ifndef RS_LIBHTTPSERVER_GZIP_RESPONSE_STREAM_H
#define	RS_LIBHTTPSERVER_GZIP_RESPONSE_STREAM_H

#include <string.h>

#include <boost/noncopyable.hpp>

#include <zlib.h>

#include "stream.h"
#include "exceptions.h"

namespace rs {
namespace httpserver {

class GzipResponseStream final : public Stream, private boost::noncopyable {
public:
    GzipResponseStream(Stream& stream);    
    ~GzipResponseStream();
    
    virtual void Flush() override;

    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override {
        throw InvalidStreamOperationException();
    }
    
    virtual int Write(const byte* buffer, int offset, int count) override;
    
    virtual long getPosition() override { return position_; }
    
    virtual long getLength() override { return length_; }

private:
    Stream& stream_;
    long position_;
    long length_;
    
    ::z_stream zStream_;
};

}}

#endif	/* RS_LIBHTTPSERVER_GZIP_RESPONSE_STREAM_H */