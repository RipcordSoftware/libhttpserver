#include "multipart_response_stream.h"

#include <cstring>

#include "exceptions.h"
#include "null_stream.h"

#define MULTIPART_RESPONSE_STREAM_BOUNDARY "b8fab5184c29c9038f729361d27d1935"
#define MULTIPART_RESPONSE_STREAM_BOUNDARY_START "--" MULTIPART_RESPONSE_STREAM_BOUNDARY "\r\n"
#define MULTIPART_RESPONSE_STREAM_BOUNDARY_END "\r\n--" MULTIPART_RESPONSE_STREAM_BOUNDARY "--"

const char* rs::httpserver::MultipartResponseStream::boundary = MULTIPART_RESPONSE_STREAM_BOUNDARY;
const char* rs::httpserver::MultipartResponseStream::boundaryStart = MULTIPART_RESPONSE_STREAM_BOUNDARY_START;
const char* rs::httpserver::MultipartResponseStream::boundaryEnd = MULTIPART_RESPONSE_STREAM_BOUNDARY_END;
const unsigned rs::httpserver::MultipartResponseStream::boundaryEndLength = std::strlen(boundaryEnd);

rs::httpserver::MultipartResponseStream::MultipartResponseStream(Stream& stream) : stream_(stream) {

}

void rs::httpserver::MultipartResponseStream::Flush() {
    Stream::Write(stream_, boundaryEnd, 0, boundaryEndLength);
    stream_.Flush();
}

int rs::httpserver::MultipartResponseStream::Read(Stream::byte*, int, int, bool) {
    throw InvalidStreamOperationException();
}

int rs::httpserver::MultipartResponseStream::Write(const Stream::byte* buffer, int offset, int count) {
    return stream_.Write(buffer, offset, count);
}

long rs::httpserver::MultipartResponseStream::getPosition() {
    return stream_.getPosition();
}

long rs::httpserver::MultipartResponseStream::getLength() {
    return stream_.getLength();
}

void rs::httpserver::MultipartResponseStream::EmitPart(const ResponseHeaders& headers) {
    std::string headerBuffer;
    headerBuffer.resize(256);
    
    if (partCount_ > 0) {
        headerBuffer += "\r\n";
    }
    
    headerBuffer += boundaryStart;
    for (auto i : headers) {
        headerBuffer += i.first + ": " + i.second + "\r\n";
    }
    
    headerBuffer += "\r\n";
        
    Stream::Write(stream_, headerBuffer);
    
    ++partCount_;
}