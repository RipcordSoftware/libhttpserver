#ifndef RS_LIBHTTPSERVER_RESPONSE_H
#define	RS_LIBHTTPSERVER_RESPONSE_H

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "types.h"

namespace rs {
namespace httpserver {

class Response : public boost::enable_shared_from_this<Response>, private boost::noncopyable {
public:
    static response_ptr Create(socket_ptr socket) {
        return response_ptr(new Response(socket));
    }
    
    
private:
    Response(socket_ptr socket) : socket_(socket) {}
    
    socket_ptr socket_;
};

}}

#endif	/* RS_LIBHTTPSERVER_RESPONSE_H */