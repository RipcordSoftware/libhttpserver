#include "gzip_response_stream.h"

#include <array>

rs::httpserver::GzipResponseStream::GzipResponseStream(Stream& stream) : stream_(stream) {
    ::memset(&zStream_, 0, sizeof(zStream_));
     ::deflateInit2(&zStream_, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 31, 9, Z_DEFAULT_STRATEGY);
}

rs::httpserver::GzipResponseStream::~GzipResponseStream() {
    ::deflateEnd(&zStream_);
}

int rs::httpserver::GzipResponseStream::Write(const byte* buffer, int offset, int count) {    
    if (count > 0) {
        std::array<Stream::byte, 2048> zBuffer;

        zStream_.next_in = const_cast<byte*>(buffer + offset);
        zStream_.avail_in = count;

        while (zStream_.avail_in > 0) {
            zStream_.next_out = zBuffer.data();
            zStream_.avail_out = zBuffer.size();

            if (::deflate(&zStream_, Z_NO_FLUSH) != Z_OK) {
                throw GzipCompressionException();
            }

            auto size = zBuffer.size() - zStream_.avail_out;
            if (size > 0) {
                stream_.Write(zBuffer.data(), 0, size);
            }
        }
    }    
    
    return count;
}

void rs::httpserver::GzipResponseStream::Flush() {     
    std::array<Stream::byte, 2048> zBuffer;
    
    zStream_.next_in = nullptr;
    zStream_.avail_in = 0;
    
    auto status = Z_OK;
    while (status == Z_OK) {
        zStream_.next_out = zBuffer.data();
        zStream_.avail_out = zBuffer.size();

        status = ::deflate(&zStream_, Z_FINISH);
        if (status != Z_OK && status != Z_STREAM_END) {
            throw GzipCompressionException();
        }
        
        auto size = zBuffer.size() - zStream_.avail_out;
        if (size > 0) {
            stream_.Write(zBuffer.data(), 0, size);
        }
    }
    
    stream_.Flush(); 
}