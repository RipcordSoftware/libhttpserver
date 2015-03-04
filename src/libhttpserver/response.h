#ifndef RS_LIBHTTPSERVER_RESPONSE_H
#define	RS_LIBHTTPSERVER_RESPONSE_H

#include <string>
#include <map>
#include <iostream>

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "types.h"
#include "response_stream.h"
#include "header_key_comparer.h"
#include "headers.h"
#include "request.h"

namespace rs {
namespace httpserver {

class Response final : public boost::enable_shared_from_this<Response>, private boost::noncopyable {
public:
    typedef std::map<std::string, std::string, HeaderKeyComparer> headers;
    
    ~Response() noexcept {}
    
    static response_ptr Create(socket_ptr socket, request_ptr request) {
        return response_ptr(new Response(socket, request));
    }
    
    Response& setStatusCode(int statusCode) {
        statusCode_ = statusCode;
        return *this;
    }
    
    Response& setStatusDescription(const std::string& statusDescription) {
        statusDescription_ = statusDescription;
        return *this;
    }    
    
    Response& setContentType(const std::string& contentType) {
        headers_[Headers::ContentType] = contentType;
        return *this;
    }
    
    Response& setContentEncoding(const std::string& contentEncoding) {
        headers_[Headers::ContentEncoding] = contentEncoding;
        return *this;
    }
    
    Response& setContentLength(int contentLength) {
        headers_[Headers::ContentLength] = boost::lexical_cast<std::string>(contentLength);
        return *this;
    }
    
    Response& setHeader(const std::string& key, const std::string& value) {
        headers_[key] = value;
        return *this;
    }
    
    bool ShouldClose() {
        auto connection = headers_.find(Headers::Connection);
        return connection != headers_.cend() ? boost::iequals(connection->second, "close") : false;
    }
    
    void Send(const std::string& data);
    void Send(Stream& stream);
    
private:
    Response(socket_ptr socket, request_ptr request) : socket_(socket), request_(request),
        responseStream_(socket_), statusCode_(200), version_(Headers::Http11), 
        headers_({{Headers::ContentType, "text/plain"}}) {}
        
    void SerializeHeaders(std::stringstream& sout);
    
    bool HasContentLength() {
        return headers_.find(Headers::ContentLength) != headers_.cend();
    }
    
    socket_ptr socket_;
    request_ptr request_;
    headers headers_;
    ResponseStream responseStream_;
    
    int statusCode_;
    std::string statusDescription_;
    std::string version_;
    
    const static std::string keepAliveHeaderValue_;
};

}}

#endif	/* RS_LIBHTTPSERVER_RESPONSE_H */