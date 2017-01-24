#include <boost/date_time.hpp>
#include <boost/format.hpp>

#include "response.h"
#include "config.h"
#include "readable_string_stream.h"
#include "chunked_response_stream.h"
#include "gzip_response_stream.h"

const std::string rs::httpserver::Response::emptyValue_;
const std::string rs::httpserver::Response::keepAliveHeaderValue_ = std::string("timeout=") + boost::lexical_cast<std::string>(Config::KeepAliveTimeout);

void rs::httpserver::Response::Send() {
    getResponseStream().Flush();
}

void rs::httpserver::Response::Send(const std::string& data) {
    ReadableStringStream stream(data);
    setContentLength(data.length()).Send(stream);
}

void rs::httpserver::Response::Send(Stream& inStream) {
    auto& responseStream = getResponseStream();
    Stream::Copy(inStream, responseStream);
    responseStream.Flush();
}

void rs::httpserver::Response::Send(std::iostream& inStream) {
    auto& responseStream = getResponseStream();
    Stream::Copy(inStream, responseStream);
    responseStream.Flush();
}

void rs::httpserver::Response::SendContinue(bool kontinue) {
    if (socketBytesSentContinue_ > 0) {
        throw MultipleContinueResponseException{};
    }
    
    const char* header = "HTTP/1.1 100 Continue\r\n\r\n";    
    if (!kontinue) {        
        header = "HTTP/1.1 417 Expectation Failed\r\nContent-Length: 0\r\n\r\n";
    }

    socketBytesSentContinue_ = std::strlen(header);
    socket_->Send(reinterpret_cast<const rs::httpserver::Stream::byte*>(header), socketBytesSentContinue_);
}

rs::httpserver::Stream& rs::httpserver::Response::getResponseStream() {
    if (HasResponded()) {
        throw MultipleResponseException{};
    }
    
    if (!request_->IsHttp10() && !HasContentLength() && statusCode_ != 304) {
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
                return zStream_;
            } else {
                return chunkedStream_;
            }
        } else {
            return responseStream_;
        }
    } else {
        return nullStream_;
    }    
}

rs::httpserver::MultipartResponseStream& rs::httpserver::Response::getMultiResponseStream() {
    if (multiStream_.getPartCount() == 0) {
        if (HasResponded()) {
            throw MultipleResponseException{};
        }
        
        headers_.erase(Headers::ContentLength);
        
        forceClose_ = true;
        headers_[Headers::ContentType] = (boost::format("multipart/related; boundary=\"%1%\"") % MultipartResponseStream::boundary).str();
        
        std::stringstream headers;
        SerializeHeaders(headers);

        socket_->Send(headers.str());
    }
    
    return multiStream_;
}

rs::httpserver::Response& rs::httpserver::Response::setETag(const std::string& etag) {
    if (etag.length() > 1 && etag[0] != '"' && etag[etag.length() - 1] != '"') {
        std::string value = '"' + etag + '"';
        return setHeader(Headers::ETag, value);
    } else {
        return setHeader(Headers::ETag, etag);
    }
}

rs::httpserver::Response& rs::httpserver::Response::setLastModified(const std::string& lastModifiedTime) {    
    return setHeader(Headers::LastModified, lastModifiedTime);
}

rs::httpserver::Response& rs::httpserver::Response::setLastModified(std::time_t lastModifiedTime) {
    auto formattedTime = Response::FormatLastModifiedTime(lastModifiedTime);    
    return setHeader(Headers::LastModified, formattedTime);
}

rs::httpserver::Response& rs::httpserver::Response::setNoCache() {
    return setHeader(Headers::Pragma, "no-cache").
            setHeader(Headers::CacheControl, "max-age=0, no-cache, no-store").
            setHeader(Headers::LastModified, "Mon, 1 Jan 1990 00:00:00 GMT").
            setHeader(Headers::ETag, emptyValue_);
}

rs::httpserver::Response& rs::httpserver::Response::setContentRange(const std::string& range) {
    return setHeader(rs::httpserver::Headers::ContentRange, range);
}

std::string rs::httpserver::Response::FormatLastModifiedTime(std::time_t lastModifiedTime) {
    auto ptime = boost::posix_time::from_time_t(lastModifiedTime);
    auto date = ptime.date();
    auto time = ptime.time_of_day();
    auto formattedTime = boost::format("%1%, %2% %3% %4% %|5$02d|:%|6$02d|:%|7$02d| GMT") %
        date.day_of_week().as_short_string() %
        date.day() % date.month().as_short_string() % date.year() %
        time.hours() % time.minutes() % time.seconds();
    
    return formattedTime.str();
}

void rs::httpserver::Response::Redirect(const std::string& location) {
    ResetHeaders();

    if (request_->getHeaders()->getVersion() == Headers::Http10) {
        setStatusCode(302);
        setStatusDescription("Found");
    } else {
        setStatusCode(307);
        setStatusDescription("Temporary Redirect");
    }
    setHeader(Headers::Location, location);
    Send();
}

void rs::httpserver::Response::SerializeHeaders(std::stringstream& sout) {
    if (request_->IsHttp10()) {
        version_ = Headers::Http10;
        headers_[Headers::Connection] = "close";
        headers_.erase(Headers::KeepAlive);
        headers_.erase(Headers::TransferEncoding);
    } else if (!forceClose_ && request_->IsKeepAlive()) {
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