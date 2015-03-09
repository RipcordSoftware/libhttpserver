#include "chunked_request_stream.h"

#include <algorithm>

const rs::httpserver::Stream::byte rs::httpserver::ChunkedRequestStream::endOfLine_[2] = { '\r', '\n' };

int rs::httpserver::ChunkedRequestStream::Read(byte* buffer, int offset, int count, bool peek) {
    if (chunkLength_ <= 0) {
        ReadHeader();
    }
    
    int bytesRead = 0;
    
    // if we know the chunk length then we can start to read it
    if (chunkLength_ > 0) {
        bytesRead = stream_.Read(buffer, offset, std::min(chunkLength_ - chunkPosition_, count), peek);
        
        // if we have read some of the chunk data then move the internal counters
        if (!peek && bytesRead > 0) {
            position_ += bytesRead;
            length_ += bytesRead;
            chunkPosition_ += bytesRead;
            
            // if we have reached the end of the chunk then eat the chunk terminator and reset the counters
            if (chunkPosition_ == chunkLength_) {
                byte temp[2];
                stream_.Read(temp, 0, sizeof(temp));
                chunkLength_ = 0;
                chunkPosition_ = 0;
            }
        }
    }
    
    return bytesRead;
}

void rs::httpserver::ChunkedRequestStream::ReadHeader() {
    byte temp[64];
    int tempBytesRead = 0, totalTempBytesRead = 0, tempChunkLength = 0, tempHeaderLength = 0;
    bool gotHeader = false;

    // attempt to read the chunk header
    while (!gotHeader && (tempBytesRead = stream_.Read(temp, totalTempBytesRead, sizeof(temp) - totalTempBytesRead, true)) > 0) {
        gotHeader = GetChunkSize(temp, totalTempBytesRead + tempBytesRead, tempChunkLength, tempHeaderLength);

        // we haven't got the header yet, so read the bytes for real
        if (!gotHeader) {
            stream_.Read(temp, totalTempBytesRead, tempBytesRead);
            totalTempBytesRead += tempBytesRead;
            
            if (totalTempBytesRead == sizeof(temp)) {
                throw ChunkedRequestHeaderException();
            }
        }
    }

    // eat any header bytes we haven't already read
    if (gotHeader) {
        stream_.Read(temp, 0, tempHeaderLength - totalTempBytesRead);
        chunkLength_ = tempChunkLength;
        chunkPosition_ = 0;

        if (chunkLength_ == 0) {
            byte temp[2];
            stream_.Read(temp, 0, sizeof(temp));
        }
    }    
}

bool rs::httpserver::ChunkedRequestStream::GetChunkSize(const byte* buffer, const int bufferLength, int& chunkLength, int& headerLength) {
    auto bufferStart = buffer, bufferEnd = buffer + bufferLength;
    auto headerEnd = std::search(bufferStart, bufferEnd, endOfLine_, endOfLine_ + sizeof(endOfLine_));
    
    auto found = headerEnd != bufferEnd;
    if (found) {
        chunkLength = 0;
        while ((*buffer >= '0' && *buffer <= '9') || (*buffer >= 'a' && *buffer <= 'f') || (*buffer >= 'A' && *buffer <= 'F')) {
            auto temp = (*buffer) - 0x30;
            if (temp > 9) {
                temp -= 0x07;
            }
            if (temp > 15) {
                temp -= 0x20;
            }
            
            chunkLength <<= 4;
            chunkLength |= temp;
            buffer++;
        }
        
        headerEnd += sizeof(endOfLine_);
        headerLength = headerEnd - bufferStart;
    }
    
    return found;
}