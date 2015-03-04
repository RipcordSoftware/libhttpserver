#include "response.h"
#include "config.h"
#include "string_stream.h"

const std::string rs::httpserver::Response::keepAliveHeaderValue_ = std::string("timeout=") + boost::lexical_cast<std::string>(Config::KeepAliveTimeout);

void rs::httpserver::Response::Send(const std::string& data) {
    StringStream stream(data);
    setContentLength(data.length()).Send(stream);
}

void rs::httpserver::Response::Send(Stream& stream) {
    std::stringstream headers;
    SerializeHeaders(headers);
    
    socket_->Send(headers.str());
    
    if (!request_->IsHead()) {
        Stream::byte buffer[2048];
        
        int bytesRead = 0;
        while ((bytesRead = stream.Read(buffer, 0, sizeof(buffer))) > 0) {
            responseStream_.Write(buffer, 0, bytesRead);
        }
    }
    
    responseStream_.Flush();
}

void rs::httpserver::Response::SerializeHeaders(std::stringstream& sout) {
    const auto isHttp10 = request_->IsHttp10();
    
    if (isHttp10) {
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
    
    // TODO: enable when chunked encoding is ready
    /*if (!isHttp10 && !HasContentLength()) {
        headers_[Headers::TransferEncoding] = "chunked";
    }*/
    
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