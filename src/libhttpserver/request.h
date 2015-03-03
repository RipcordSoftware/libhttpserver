#ifndef RS_LIBHTTPSERVER_REQUEST_H
#define RS_LIBHTTPSERVER_REQUEST_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

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
    
private:
    Request(request_headers_ptr request_headers) : request_headers_(request_headers), queryString_(request_headers->getQueryString()) {}
    
    const request_headers_ptr request_headers_;
    const QueryString queryString_;

};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_H */

