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
#include "null_stream.h"
#include "headers.h"

namespace rs {
namespace httpserver {

/**
 * A class which handles the specifics of an HTTP request
 */
class Request final : public boost::enable_shared_from_this<Request>, private boost::noncopyable {
public:
    static request_ptr Create(socket_ptr socket, request_headers_ptr request_headers, HeaderBuffer& headerBuffer) {
        return request_ptr(new Request(socket, request_headers, headerBuffer));
    }
    
    /**
     * Gets the request headers object
     * @return The headers of the request
     */
    request_headers_ptr getHeaders() {
        return request_headers_;
    }
    
    /**
     * Gets the query string
     * @return the requests query string
     */
    const QueryString& getQueryString() {
        return queryString_;
    }
    
    /**
     * Returns true if the request is HTTP/1.0
     * @return true if the client is using HTTP/1.0
     */
    bool IsHttp10() {
        return request_headers_->getVersion() == Headers::Http10;
    }
    
    /**
     * Returns true if the client has requested keep-alive
     * @return true if the client explicitly wants to keep the connection open
     */
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
    
    /**
     * Returns true if the request method is a HEAD
     * @ return true if the request is a HEAD
     */
    bool IsHead() {
        return request_headers_->getMethod() == Headers::Head;
    }
    
    /**
     * Returns true if the client will accept GZIP encoded responses
     * @return true if the client accepts GZIP
     */
    bool ClientAcceptsGzip() {
        auto acceptEncoding = request_headers_->getAcceptEncoding();
        return acceptEncoding.length() > 0 && acceptEncoding.find("gzip") != std::string::npos;
    }

    /**
     * The uri the client used to make the request
     * @return The request uri
     */
    const std::string& getUri() {
        return request_headers_->getUri();
    }
    
    /**
     * Gets the request method (i.e. GET, PUT, POST, etc)
     * @return the method used in the request
     */
    const std::string& getMethod() {
        return request_headers_->getMethod();
    }        
    
    /**
     * Gets connection header passed by the client
     * @return The connection header
     */
    const std::string& getConnection() {
        return request_headers_->getConnection();
    }
    
    /**
     * Gets the content type of the request body
     * @return The request body content type
     */
    const std::string& getContentType() {
        return request_headers_->getContentType();
    }
    
    /**
     * Gets the Accept-Encoding field of the request header
     * @return the Accept-Encoding header
     */
    const std::string& getAcceptEncoding() {
        return request_headers_->getAcceptEncoding();
    }
    
    /**
     * Gets the If-None-Match request header
     * @param trimQuotes when true the header field will be returned without the enclosing quotes
     * @return The If-None-Match header
     */
    std::string getIfNoneMatch(bool trimQuotes = true) {
        auto etag = request_headers_->getIfNoneMatch();
        
        // trim off the quotes
        if (trimQuotes && etag.length() > 1 && etag[0] == '"' && etag[etag.length() - 1] == '"') {
            etag = etag.substr(1, etag.length() - 2);
        }
        
        return etag;
    }

    /**
     * Gets the literal Range header
     * @return The literal (unparsed) range header
     */    
    const std::string& getRange() const {
        return request_headers_->getRange();
    }
    
    /**
     * Gets the Range header and unpicks any byte ranges
     * @return Byte ranges as pairs
     */    
    RequestHeaders::byte_range_collection getByteRanges() {
        return request_headers_->getByteRanges();
    }
    
    /**
     * Gets the If-Modified-Since request header
     * @return The If-Modified-Since header
     */
    const std::string& getIfModifiedSince() {
        return request_headers_->getIfModifiedSince();
    }
    
    /**
     * Gets the length of the request body
     * @return the length of the request body
     */
    int getContentLength() {
        return request_headers_->getContentLength();
    }
    
    /**
     * A helper to determine whether the client wants the server to close the connection
     * after the response has been sent
     * @return true if the client has requested that the connection should be closed
     */
    bool ShouldClose();
    
    /**
     * Gets the request body stream
     * @return the request body stream
     */
    Stream& getRequestStream();
    
    /**
     * Determines whether the request has a body or not
     * @return True if the request is a PUT or POST and it has a body and content type
     */
    bool HasBody();
    
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
    static NullStream nullStream_;

};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_H */

