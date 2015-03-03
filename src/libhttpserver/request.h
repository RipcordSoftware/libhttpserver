#ifndef RS_LIBHTTPSERVER_REQUEST_H
#define	RS_LIBHTTPSERVER_REQUEST_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "types.h"
#include "request_headers.h"

namespace rs {
namespace httpserver {

class Request : public boost::enable_shared_from_this<Request>, private boost::noncopyable {
public:
    static request_ptr Create(request_headers_ptr request_headers) {
        return request_ptr(new Request(request_headers));
    }
    
    request_headers_ptr getHeaders() {
        return request_headers_;
    }
    
private:
    Request(request_headers_ptr request_headers) : request_headers_(request_headers) {}
    
    const request_headers_ptr request_headers_;

};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_H */

