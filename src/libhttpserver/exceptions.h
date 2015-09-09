#ifndef RS_LIBHTTPSERVER_EXCEPTIONS_H
#define	RS_LIBHTTPSERVER_EXCEPTIONS_H

#include <exception>

namespace rs {
namespace httpserver {

class HttpServerException : public std::exception {
};

class InvalidBufferDataLengthException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "Invalid buffer data length specified";
};

class InvalidBufferPositionException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "Invalid buffer position specified";
};

class HeaderTimeoutException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "Timed out waiting for request headers";
};

class HeaderSizeException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "The request header was too large";
};

class HeaderMalformedException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "The request header was malformed";
};

class InvalidStreamOperationException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "The stream operation was invalid";
};

class SocketWriteException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "Unable to write data to the socket";
};

class MultipleResponseException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "The response can only be sent to the client once";
};

class MultipleContinueResponseException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "The continue response can only be sent to the client once";
};

class GzipCompressionException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "There was an error in the gzip compressor";
};

class ChunkedRequestHeaderException : public HttpServerException {
public:
    virtual const char* what() const noexcept override {
        return what_;
    }    
private:
    const char* what_ = "There was an error reading the chunked request data";
};

}}

#endif	/* RS_LIBHTTPSERVER_EXCEPTIONS_H */

