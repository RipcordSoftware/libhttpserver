#include "multipart_response_stream.h"

#include <cstring>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "exceptions.h"
#include "null_stream.h"
#include "headers.h"

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

void rs::httpserver::MultipartResponseStream::EmitPart(const char* contentType, const char* filename, std::int64_t contentLength) {
    std::string headerBuffer;
    headerBuffer.reserve(256);

    if (partCount_ > 0) {
        headerBuffer += "\r\n";
    }        

    headerBuffer += boundaryStart;    
    headerBuffer += Headers::ContentType + ": " + contentType + "\r\n";
    
    if (filename) {
        headerBuffer += Headers::ContentDisposition + ": " + (boost::format("attachment; filename=\"%1%\"") % filename).str() + "\r\n";
    }
    
    if (contentLength >= 0) {
        headerBuffer += Headers::ContentLength + ": " + boost::lexical_cast<std::string>(contentLength) + "\r\n";
    }
    
    headerBuffer += "\r\n";
        
    Stream::Write(stream_, headerBuffer);
    
    ++partCount_;
}