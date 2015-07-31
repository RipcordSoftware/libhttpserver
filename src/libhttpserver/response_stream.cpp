#include "response_stream.h"

void rs::httpserver::ResponseStream::Flush() {
    socket_->Flush();
}

int rs::httpserver::ResponseStream::Write(const Stream::byte* buffer, int offset, int count) {
    auto written = 0;
    
    while (written < count) {
        auto sentBytes = socket_->Send(buffer + offset + written, count - written);
        if (sentBytes <= 0) {
            throw SocketWriteException();
        }
        
        written += sentBytes;
        position_ += sentBytes;
        length_ += sentBytes;
    }
    
    return written;
}