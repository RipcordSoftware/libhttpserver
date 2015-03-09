#ifndef RS_LIBHTTPSERVER_REQUEST_H
#define RS_LIBHTTPSERVER_REQUEST_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/algorithm/string.hpp>

#include "types.h"
#include "request_headers.h"
#include "query_string.h"
#include "request_stream.h"
#include "chunked_request_stream.h"
#include "headers.h"

namespace rs {
namespace httpserver {

class Request final : public boost::enable_shared_from_this<Request>, private boost::noncopyable {
public:
    static request_ptr Create(socket_ptr socket, request_headers_ptr request_headers, HeaderBuffer& headerBuffer) {
        return request_ptr(new Request(socket, request_headers, headerBuffer));
    }
    
    request_headers_ptr getHeaders() {
        return request_headers_;
    }
    
    const QueryString& getQueryString() {
        return queryString_;
    }
    
    bool IsHttp10() {
        return request_headers_->getVersion() == Headers::Http10;
    }
    
    bool IsKeepAlive() {
        auto keepAlive = true;
        auto connection = request_headers_->getConnection();
        
        if (IsHttp10()) {
            keepAlive = boost::iequals(connection, "keep-alive");
        } else {
            keepAlive = !boost::iequals(connection, "close");
        }
        
        return keepAlive;
    }
    
    bool IsHead() {
        return request_headers_->getMethod() == Headers::Head;
    }
    
    bool ClientAcceptsGzip() {
        auto acceptEncoding = request_headers_->getAcceptEncoding();
        return acceptEncoding.length() > 0 && acceptEncoding.find("gzip") != std::string::npos;
    }

    const std::string& getUri() {
        return request_headers_->getUri();
    }
    
    const std::string& getMethod() {
        return request_headers_->getMethod();
    }        
    
    const std::string& getConnection() {
        return request_headers_->getConnection();
    }
    
    const std::string& getContentType() {
        return request_headers_->getContentType();
    }
    
    const std::string& getAcceptEncoding() {
        return request_headers_->getAcceptEncoding();
    }
    
    int getContentLength() {
        return request_headers_->getContentLength();
    }
    
    bool ShouldClose() {
        auto connection = getConnection();
        if (boost::iequals(connection, "close")) {
            return true;
        } else if (IsHttp10() && connection.length() == 0) {
            return true;
        } else {
            return false;
        }
    }
    
    Stream& getRequestStream() {
        if (request_headers_->IsChunked()) {
            return chunkedRequestStream_;
        } else {
            return requestStream_;
        }
    }
    
private:
    Request(socket_ptr socket, request_headers_ptr request_headers, HeaderBuffer& headerBuffer) : 
        socket_(socket), request_headers_(request_headers),
        queryString_(request_headers->getQueryString()),
        requestStream_(socket, headerBuffer), chunkedRequestStream_(requestStream_) {}
    
    const socket_ptr socket_;
    const request_headers_ptr request_headers_;
    const QueryString queryString_;
    RequestStream requestStream_;
    ChunkedRequestStream chunkedRequestStream_;

};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_H */

