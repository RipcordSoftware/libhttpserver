#ifndef RS_LIBHTTPSERVER_EXCEPTIONS_H
#define	RS_LIBHTTPSERVER_EXCEPTIONS_H

#include <exception>
#include <string>

namespace rs {
namespace httpserver {

class HttpServerException : public std::exception {
public:
    HttpServerException(const char* what) : what_(what) {}
    
protected:
    std::string what_;
};

class InvalidBufferDataLengthException : public HttpServerException {
public:
    InvalidBufferDataLengthException() : HttpServerException("Invalid buffer data length specified") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }    
};

class InvalidBufferPositionException : public HttpServerException {
public:
    InvalidBufferPositionException() : HttpServerException("Invalid buffer position specified") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class HeaderTimeoutException : public HttpServerException {
public:
    HeaderTimeoutException(int receivedBytes) : 
        HttpServerException("Timed out waiting for request headers"),
        receivedBytes_(receivedBytes) {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
    
    const int receivedBytes_;
};

class HeaderSizeException : public HttpServerException {
public:
    HeaderSizeException() : HttpServerException("The request header was too large") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class HeaderMalformedException : public HttpServerException {
public:
    HeaderMalformedException() : HttpServerException("The request header was malformed") {}
    
    HeaderMalformedException(const char* reason) : HeaderMalformedException() {        
        what_ += " (";
        what_ += reason;
        what_ += ")";
    }
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class InvalidStreamOperationException : public HttpServerException {
public:
    InvalidStreamOperationException() : HttpServerException("The stream operation was invalid") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class SocketWriteException : public HttpServerException {
public:
    SocketWriteException() : HttpServerException("Unable to write data to the socket") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class MultipleResponseException : public HttpServerException {
public:
    MultipleResponseException() : HttpServerException("The response can only be sent to the client once") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class MultipleContinueResponseException : public HttpServerException {
public:
    MultipleContinueResponseException() : HttpServerException("The continue response can only be sent to the client once") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class GzipCompressionException : public HttpServerException {
public:
    GzipCompressionException() : HttpServerException("There was an error in the gzip compressor") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

class ChunkedRequestHeaderException : public HttpServerException {
public:
    ChunkedRequestHeaderException() : HttpServerException("There was an error reading the chunked request data") {}
    
    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};

}}

#endif	/* RS_LIBHTTPSERVER_EXCEPTIONS_H */

