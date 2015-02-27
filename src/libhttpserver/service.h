#ifndef RS_LIBHTTPSERVER_SERVICE_H
#define	RS_LIBHTTPSERVER_SERVICE_H

#include <string>

#include <boost/shared_ptr.hpp>
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
    typedef boost::function<void (socket_ptr, const boost::system::error_code &)> listen_callback;
    
    static service_ptr Create(int threads) {
        return service_ptr(new Service(threads));
    }       
   
    void Run() { service_->run(); }        
    
    void Listen(const std::string& host, int port, listen_callback func);
    
    operator boost::asio::io_service&() { return *service_; }
    
private:
    Service(int threads) : service_(new boost::asio::io_service(threads)) {}       
    
    static void StartAccept(socket_ptr socket, listen_callback func);
    static void HandleAccept(socket_ptr socket, listen_callback func, const boost::system::error_code& error);
    
    asio_io_service_ptr service_;
};
    
}}
#endif	/* RS_LIBHTTPSERVER_SERVICE_H */

