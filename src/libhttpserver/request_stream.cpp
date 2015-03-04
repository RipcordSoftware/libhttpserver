#include "request_stream.h"
#include "config.h"

int rs::httpserver::RequestStream::Read(Stream::byte* buffer, int offset, int count, bool peek) {
    auto bytes = 0;

    if (headerBuffer_.HasData()) {
        bytes += headerBuffer_.Copy(reinterpret_cast<HeaderBuffer::value_type*>(buffer + offset), count);
        offset += bytes;
        count -= bytes;
    }        

    if (count > 0 && (bytes == 0 || socket_->Available())) {
        auto socketBytes = socket_->Receive(Config::BodyReceiveTimeoutPeriod, buffer + offset, count, peek);
        if (socketBytes > 0) {
            bytes += socketBytes;            
        }
    }
    
    if (!peek) {
        position_ += bytes;
        length_ += bytes;
    }

    return bytes;
}