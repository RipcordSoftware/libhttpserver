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
        
        if (request_->ClientAcceptsGzip()) {
            headers_[Headers::ContentEncoding] = "gzip";
        }
    }
    
    std::stringstream headers;
    SerializeHeaders(headers);
    
    socket_->Send(headers.str());
    
    if (!request_->IsHead()) {
        if (IsChunkEncoded()) {
            if (request_->ClientAcceptsGzip()) {
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