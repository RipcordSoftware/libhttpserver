#include "gzip_response_stream.h"

rs::httpserver::GzipResponseStream::GzipResponseStream(Stream& stream) : stream_(stream) {
    ::memset(&zStream_, 0, sizeof(zStream_));
     ::deflateInit2(&zStream_, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 31, 9, Z_DEFAULT_STRATEGY);
}

rs::httpserver::GzipResponseStream::~GzipResponseStream() {
    ::deflateEnd(&zStream_);
}

int rs::httpserver::GzipResponseStream::Write(const byte* buffer, int offset, int count) {    
    if (count > 0) {
        Stream::byte zBuffer[2048];

        auto prevTotalOut = zStream_.total_out;

        zStream_.next_in = const_cast<byte*>(buffer + offset);
        zStream_.avail_in = count;
        zStream_.next_out = zBuffer;
        zStream_.avail_out = sizeof(zBuffer);

        if (::deflate(&zStream_, Z_SYNC_FLUSH) != Z_OK) {
            throw GzipCompressionException();
        }
        
        stream_.Write(zBuffer, 0, zStream_.total_out - prevTotalOut);
    }    
    
    return count;
}

void rs::httpserver::GzipResponseStream::Flush() {     
    Stream::byte zBuffer[2048];
    
    auto prevTotalOut = zStream_.total_out;
    
    zStream_.next_in = nullptr;
    zStream_.avail_in = 0;
    zStream_.next_out = zBuffer;
    zStream_.avail_out = sizeof(zBuffer);
    
    if (::deflate(&zStream_, Z_FINISH) != Z_STREAM_END) {
        throw GzipCompressionException();
    }
        
    stream_.Write(zBuffer, 0, zStream_.total_out - prevTotalOut);
    
    stream_.Flush(); 
}