#ifndef RS_LIBHTTPSERVER_REQUEST_H
#define RS_LIBHTTPSERVER_REQUEST_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/algorithm/string.hpp>

#include "types.h"
#include "request_headers.h"
#include "query_string.h"

namespace rs {
namespace httpserver {

class Request final : public boost::enable_shared_from_this<Request>, private boost::noncopyable {
public:
    static request_ptr Create(request_headers_ptr request_headers) {
        return request_ptr(new Request(request_headers));
    }
    
    request_headers_ptr getHeaders() {
        return request_headers_;
    }
    
    const QueryString& getQueryString() {
        return queryString_;
    }
    
    bool IsHttp10() {
        return request_headers_->getVersion() == "HTTP/1.0";
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
    
private:
    Request(request_headers_ptr request_headers) : request_headers_(request_headers), queryString_(request_headers->getQueryString()) {}
    
    const request_headers_ptr request_headers_;
    const QueryString queryString_;

};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_H */

