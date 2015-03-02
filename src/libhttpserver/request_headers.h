#ifndef RS_LIBHTTPSERVER_REQUEST_HEADERS_H
#define	RS_LIBHTTPSERVER_REQUEST_HEADERS_H

#include <map>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "header_buffer.h"
#include "types.h"

namespace rs {
namespace httpserver {

class RequestHeaders final : public boost::enable_shared_from_this<RequestHeaders>, private boost::noncopyable {
public:    
    
    static request_headers_ptr Create(const HeaderBuffer& buffer);
    
    const std::string& getMethod() {
        return method_;
    }
    
    const std::string& getUri() {
        return uri_;
    }
    
    const std::string& getVersion() {
        return version_;
    }
    
    const std::string& getHeader(const std::string& field) {
        auto value = headers_.find(field);
        return value != headers_.cend() ? value->second : emptyValue_;
    }
    
    const std::string& getContentType() {
        return getHeader("Content-Type");
    }
    
    const std::string& getAcceptEncoding() {
        return getHeader("Accept-Encoding");
    }
    
    const std::string& getAccept() {
        return getHeader("Accept");
    }
    
    const std::string& getHost() {
        return getHeader("Host");
    }
    
    const std::string& getTransferEncoding() {
        return getHeader("Transfer-Encoding");
    }
    
    const std::string& getContentEncoding() {
        return getHeader("Content-Encoding");
    }
    
    const std::string& getExpect() {
        return getHeader("Expect");
    }
    
    const std::string& getUserAgent() {
        return getHeader("User-Agent");
    }
    
    const std::string& getConnection() {
        return getHeader("Connection");
    }
    
    int getContentLength() {
        if (contentLength_ < 0) {
            contentLength_ = 0;
            
            auto contentLengthValue = getHeader("Content-Length");
            if (contentLengthValue.length() > 0) {
                contentLength_ = boost::lexical_cast<int>(contentLengthValue);
            }
        }
        return contentLength_;
    }
    
private:            
    typedef std::map<std::string, std::string> headers;    
    
    RequestHeaders() : contentLength_(-1) {}
    
    void GetHeaders(const HeaderBuffer& buffer, int headersLength);    
    
    std::string method_;
    std::string version_;
    std::string uri_;
    std::string rawUrl_;    
    std::string queryString_;
    int contentLength_;        
    
    headers headers_;
    
    static const std::string emptyValue_;
    static const char endOfLine_[];
};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_HEADERS_H */