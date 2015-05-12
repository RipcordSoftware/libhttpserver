#include "chunked_response_stream.h"

const rs::httpserver::Stream::byte rs::httpserver::ChunkedResponseStream::endOfLine_[2] = { '\r', '\n' };
const rs::httpserver::Stream::byte rs::httpserver::ChunkedResponseStream::endOfBlocks_[5] = { '0', '\r', '\n', '\r', '\n' };

int rs::httpserver::ChunkedResponseStream::Write(const byte* buffer, int offset, int count) {
    auto blocks = count / Config::MaxResponseChunkSize;
    auto overflow = count % Config::MaxResponseChunkSize;

    for (int i = 0; i < blocks; i++) {
        stream_.Write(&maxBlockSizeHeader_[0], 0, maxBlockSizeHeader_.size());
        stream_.Write(buffer, offset, Config::MaxResponseChunkSize);
        stream_.Write(endOfLine_, 0, sizeof(endOfLine_));
        offset += Config::MaxResponseChunkSize;
        position_ += Config::MaxResponseChunkSize;
        length_ += Config::MaxResponseChunkSize;
    }
    
    if (overflow > 0) {
        auto header = GetHeader(overflow);
        stream_.Write(&header[0], 0, header.size());
        stream_.Write(buffer, offset, overflow);
        stream_.Write(endOfLine_, 0, sizeof(endOfLine_));
        position_ += overflow;
        length_ += overflow;
    }
        
    return count;
}

void rs::httpserver::ChunkedResponseStream::Flush() { 
    stream_.Write(endOfBlocks_, 0, sizeof(endOfBlocks_));
    stream_.Flush(); 
}

std::vector<rs::httpserver::Stream::byte> rs::httpserver::ChunkedResponseStream::GetHeader(int blockSize) {    
    if (blockSize <= 0) {
        return std::vector<Stream::byte>({'0', '\r', '\n'});
    } else {
        auto chars = 0;
        while ((blockSize >> (4 * chars)) > 0) ++chars;

        std::vector<Stream::byte> buffer(chars + 2);
        for (auto i = 0; i < chars; ++i) {
            auto index = chars - 1 - i;
            buffer[index] = (blockSize >> (4 * i)) & 0x0f;
            buffer[index] += buffer[index] > 9 ? ('a' - 10) : '0';
        }

        buffer[chars] = '\r';
        buffer[chars + 1] = '\n';    
        return buffer;
    }
}