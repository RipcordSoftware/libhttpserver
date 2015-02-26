#ifndef RS_LIBHTTPSERVER_SERVICE_H
#define	RS_LIBHTTPSERVER_SERVICE_H

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>

#include <boost/asio.hpp>

#include "types.h"
#include "socket.h"

namespace rs {
namespace httpwebserver {
    
class Service final : public boost::enable_shared_from_this<Service>, private boost::noncopyable {
public:
    static service_ptr Create(int threads) {
        return service_ptr(new Service(threads));
    }
    
    operator boost::asio::io_service&() { return *service_; }
   
    void Run() { service_->run(); }        
    
private:
    Service(int threads) : service_(new boost::asio::io_service(threads)) {}
    
    boost::scoped_ptr<boost::asio::io_service> service_;
};
    
}}
#endif	/* RS_LIBHTTPSERVER_SERVICE_H */

