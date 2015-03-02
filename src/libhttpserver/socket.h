#ifndef RS_LIBHTTPSERVER_SOCKET_H
#define	RS_LIBHTTPSERVER_SOCKET_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/asio.hpp>

#include "types.h"
#include "header_buffer.h"

namespace rs {
namespace httpserver {
    
class Socket final : public boost::enable_shared_from_this<Socket>, private boost::noncopyable {
public:
    typedef unsigned char byte;
    typedef std::vector<byte> buffer;
    
    ~Socket() {
        Shutdown();
    }
    
    static socket_ptr Create(server_ptr server, asio_socket_ptr socket);
       
    std::size_t Receive(HeaderBuffer& b);
    
    std::size_t Receive(int timeout, HeaderBuffer& b);
    
    std::size_t Send(const std::string& s) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(&s[0]), s.length()));
    }
    
    std::size_t Send(const buffer& b) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(&b[0]), b.size()));
    }
    
    void Shutdown() {
        socket_->shutdown(boost::asio::socket_base::shutdown_type::shutdown_both);
    }
    
    bool Connected() {
        return socket_->is_open();
    }
    
    asio_socket_ptr getAsioSocket() { return socket_; }    
    
    boost::asio::ip::tcp::endpoint getLocalEndpoint() { return socket_->local_endpoint(); }
    boost::asio::ip::tcp::endpoint getRemoteEndpoint() { return socket_->remote_endpoint(); }
    
private:
    
    Socket(server_ptr server, asio_socket_ptr socket) : 
        server_(server), socket_(socket) {
    }
        
    static int getReceiveTimeout(asio_socket_ptr socket);
    static bool setReceiveTimeout(asio_socket_ptr socket, int seconds);

    void setDefaultReceiveTimeout();
    void setCustomReceiveTimeout(int seconds);
            
    server_ptr server_;
    asio_socket_ptr socket_;
    
    int defaultReceiveTimeout = -1;
    int currentReceiveTimeout = -1;
};
    
}}

#endif	/* RS_LIBHTTPSERVER_SOCKET_H */

