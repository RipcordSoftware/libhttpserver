#ifndef RS_LIBHTTPSERVER_SOCKET_H
#define	RS_LIBHTTPSERVER_SOCKET_H

#include <vector>
#include <functional>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "types.h"

namespace rs {
namespace httpwebserver {
    
class Socket final : public boost::enable_shared_from_this<Socket>, private boost::noncopyable {
public:
    typedef unsigned char byte;
    typedef std::vector<byte> buffer;
    
    ~Socket() {
        Shutdown();
    }
    
    static socket_ptr Create(service_ptr service) {
        return Create(service, nullptr);
    }
    
    static socket_ptr Create(service_ptr service, asio_acceptor_ptr acceptor);
       
    std::size_t Receive(buffer& b);
    
    std::size_t Receive(int timeout, buffer& b);
    
    std::size_t Send(const std::string& s) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(&s[0]), s.size() * sizeof(std::string::value_type)));
    }
    
    std::size_t Send(const buffer& b) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(&b[0]), b.size()));
    }
    
    void Shutdown() {
        socket_->shutdown(boost::asio::socket_base::shutdown_type::shutdown_both);
    }
    
    service_ptr getService() { return service_; }
    asio_socket_ptr getAsioSocket() { return socket_; }
    asio_acceptor_ptr getAsioAcceptor() { return acceptor_; }
    
    boost::asio::ip::tcp::endpoint getLocalEndpoint() { return socket_->local_endpoint(); }
    boost::asio::ip::tcp::endpoint getRemoteEndpoint() { return socket_->remote_endpoint(); }
    
private:
    
    Socket(service_ptr service, asio_socket_ptr socket, asio_acceptor_ptr acceptor = nullptr) : 
        service_(service), socket_(socket), acceptor_(acceptor) {
    }
        
    static int getReceiveTimeout(asio_socket_ptr socket);
    static bool setReceiveTimeout(asio_socket_ptr socket, int seconds);

    void setDefaultReceiveTimeout();
    void setCustomReceiveTimeout(int seconds);
            
    service_ptr service_;
    asio_socket_ptr socket_;
    asio_acceptor_ptr acceptor_;
    
    int defaultReceiveTimeout = -1;
    int currentReceiveTimeout = -1;
};
    
}}

#endif	/* RS_LIBHTTPSERVER_SOCKET_H */

