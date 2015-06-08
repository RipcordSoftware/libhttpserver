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
#include "mime_types.h"

namespace rs {
namespace httpserver {

class Response final : public boost::enable_shared_from_this<Response>, private boost::noncopyable {
public:
    typedef std::map<std::string, std::string, HeaderKeyComparer> headers;
    
    ~Response() noexcept {}
    
    static response_ptr Create(socket_ptr socket, request_ptr request) {
        return response_ptr(new Response(socket, request));
    }
    
    int getStatusCode() {
        return statusCode_;
    }
    
    Response& setStatusCode(int statusCode) {
        statusCode_ = statusCode;
        return *this;
    }
    
    Response& setStatusDescription(const std::string& statusDescription) {
        statusDescription_ = statusDescription;
        return *this;
    }    
    
    Response& setContentType(const MimeTypes::Item& item) {
        return setContentType(item.getType(), item.getCompressible());
    }
    
    Response& setContentType(const std::string& contentType = emptyValue_, bool compress = false) {
        compress_ = compress & request_->ClientAcceptsGzip();
        return setHeader(Headers::ContentType, contentType);
    }
    
    Response& setContentEncoding(const std::string& contentEncoding = emptyValue_) {
        return setHeader(Headers::ContentEncoding, contentEncoding);
    }
    
    Response& setContentLength(int contentLength) {
        return setHeader(Headers::ContentLength, boost::lexical_cast<std::string>(contentLength));
    }
    
    Response& setLocation(const std::string& location) {
        return setHeader(Headers::Location, location);
    }
    
    Response& setLastModified(std::time_t lastModifiedTime);
    
    Response& setLastModified(const std::string& lastModifiedTime);
    
    Response& setETag(const std::string& etag);
    
    Response& setHeader(const std::string& key, const std::string& value = emptyValue_) {
        if (value.length() > 0) {
            headers_[key] = value;
        } else {
            headers_.erase(key);
        }

        return *this;
    }
    
    Response& ResetHeaders() {
        headers_.clear();
        statusCode_ = Headers::DefaultStatusCode;
        statusDescription_ = Headers::DefaultStatusDescription;
        version_ = Headers::DefaultVersion;
        return *this;
    }
    
    bool ShouldClose() {
        auto connection = headers_.find(Headers::Connection);
        return connection != headers_.cend() ? boost::iequals(connection->second, "close") : false;
    }
    
    bool HasResponded() {
        return socket_->getTotalBytesSent() != socketBytesSentWatermark_;
    }

    void Send(const std::string& data = emptyValue_);
    void Send(Stream& stream);
    
    void Redirect(const std::string& location);
    
    static std::string FormatLastModifiedTime(std::time_t lastModifiedTime);

private:
    Response(socket_ptr socket, request_ptr request) : socket_(socket), request_(request),
        responseStream_(socket_), statusCode_(Headers::DefaultStatusCode), version_(Headers::DefaultVersion), 
        statusDescription_(Headers::DefaultStatusDescription), headers_(),
        socketBytesSentWatermark_(socket->getTotalBytesSent()),
        compress_(false) {}
        
    void SerializeHeaders(std::stringstream& sout);
    
    bool HasContentLength() {
        return headers_.find(Headers::ContentLength) != headers_.cend();
    }
    
    bool IsChunkEncoded() {
        auto encoding = headers_.find(Headers::TransferEncoding);
        return encoding != headers_.cend() ? boost::iequals(encoding->second, "chunked") : false;
    }
    
    socket_ptr socket_;
    request_ptr request_;
    headers headers_;
    ResponseStream responseStream_;
    
    int statusCode_;
    std::string statusDescription_;
    std::string version_;
    
    bool compress_;
    
    const std::size_t socketBytesSentWatermark_;

    const static std::string emptyValue_;
    const static std::string keepAliveHeaderValue_;
};

}}

#endif	/* RS_LIBHTTPSERVER_RESPONSE_H */