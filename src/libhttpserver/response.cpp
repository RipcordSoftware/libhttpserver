#include <boost/date_time.hpp>
#include <boost/format.hpp>

#include "response.h"
#include "config.h"
#include "string_stream.h"
#include "chunked_response_stream.h"
#include "gzip_response_stream.h"

const std::string rs::httpserver::Response::emptyValue_;
const std::string rs::httpserver::Response::keepAliveHeaderValue_ = std::string("timeout=") + boost::lexical_cast<std::string>(Config::KeepAliveTimeout);

void rs::httpserver::Response::Send(const std::string& data) {
    StringStream stream(data);
    setContentLength(data.length()).Send(stream);
}

void rs::httpserver::Response::Send(Stream& inStream) {
    if (HasResponded()) {
        throw MultipleResponseException();
    }
    
    if (!request_->IsHttp10() && !HasContentLength()) {
        headers_[Headers::TransferEncoding] = "chunked";
        
        if (compress_) {
            headers_[Headers::ContentEncoding] = "gzip";
        }
    }
    
    std::stringstream headers;
    SerializeHeaders(headers);
    
    socket_->Send(headers.str());
    
    if (!request_->IsHead()) {
        if (IsChunkEncoded()) {
            if (compress_) {
                ChunkedResponseStream chunkedStream(responseStream_);
                GzipResponseStream zStream(chunkedStream);
                Stream::Copy(inStream, zStream);
                zStream.Flush();
            } else {
                ChunkedResponseStream chunkedStream(responseStream_);
                Stream::Copy(inStream, chunkedStream);
                chunkedStream.Flush();
            }
        } else {
            Stream::Copy(inStream, responseStream_);
            responseStream_.Flush();
        }
    }        
}

rs::httpserver::Response& rs::httpserver::Response::setETag(const std::string& etag) {
    if (etag.length() > 1 && etag[0] == '"' && etag[etag.length() - 1] == '"') {
        std::string value = '"' + etag + '"';
        return setHeader(Headers::ETag, value);
    } else {
        return setHeader(Headers::ETag, etag);
    }
}

rs::httpserver::Response& rs::httpserver::Response::setLastModified(std::time_t lastModifiedTime) {
    auto ptime = boost::posix_time::from_time_t(lastModifiedTime);
    auto date = ptime.date();
    auto time = ptime.time_of_day();
    auto formattedTime = boost::format("%1%, %2% %3% %4% %|5$02d|:%|6$02d|:%|7$02d| GMT") %
        date.day_of_week().as_short_string() %
        date.day() % date.month().as_short_string() % date.year() %
        time.hours() % time.minutes() % time.seconds();
    
    return setHeader(Headers::LastModified, formattedTime.str());
}

void rs::httpserver::Response::Redirect(const std::string& location) {
    ResetHeaders();
    setStatusCode(307);
    setStatusDescription("Moved");
    setHeader(Headers::Location, location);
    Send();
}

void rs::httpserver::Response::SerializeHeaders(std::stringstream& sout) {
    if (request_->IsHttp10()) {
        version_ = Headers::Http10;
        headers_[Headers::Connection] = "close";
        headers_.erase(Headers::KeepAlive);
        headers_.erase(Headers::TransferEncoding);
    } else if (request_->IsKeepAlive()) {
        headers_[Headers::Connection] = "keep-alive";
        headers_[Headers::KeepAlive] = keepAliveHeaderValue_;
    } else {
        headers_[Headers::Connection] = "close";
        headers_.erase(Headers::KeepAlive);
    }
    
    if (statusCode_ == 200) {
        statusDescription_ = "OK";
    }
    
    sout << version_ << " " << statusCode_;    
    if (statusDescription_.length() > 0) {
        sout << " " << statusDescription_;
    }    
    sout << "\r\n";
    
    for (auto i : headers_) {
        sout << i.first << ": " << i.second << "\r\n";
    }
    
    sout << "\r\n";
}