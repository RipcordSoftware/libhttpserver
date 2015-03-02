#ifndef RS_LIBHTTPSERVER_REQUEST_HEADERS_H
#define	RS_LIBHTTPSERVER_REQUEST_HEADERS_H

#include <map>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "header_buffer.h"
#include "types.h"

namespace rs {
namespace httpserver {

class RequestHeaders final : public boost::enable_shared_from_this<RequestHeaders>, private boost::noncopyable {
public:    
    
    static request_headers_ptr Create(const HeaderBuffer& buffer);
    
private:            
    typedef std::map<std::string, std::string> headers;    
    
    RequestHeaders() {}
    
    void GetHeaders(const HeaderBuffer& buffer, int headersLength);    
    
    std::string method_;
    std::string version_;
    std::string rawUrl_;
    std::string uri_;
    std::string queryString_;
    
    headers headers_;
    
    static const char endOfLine_[];

};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_HEADERS_H */