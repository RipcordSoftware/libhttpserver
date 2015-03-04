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
    
    class ScopedClose {
    public:
        ScopedClose(socket_ptr socket) : socket_(socket) {}
        ~ScopedClose() { socket_->Close(); }
        
    private:
        socket_ptr socket_;
    };
    
    ~Socket() {
        Shutdown();
    }
    
    static socket_ptr Create(server_ptr server, asio_socket_ptr socket);
       
    std::size_t Receive(byte* buffer, int length, bool peek = false);
    
    std::size_t Receive(int timeout, byte* buffer, int length, bool peek = false);
    
    std::size_t Send(const std::string& s) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(&s[0]), s.length()));
    }
    
    std::size_t Send(const byte* buffer, int length) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(buffer), length));
    }
    
    void Shutdown() {
        if (Connected()) {
            socket_->shutdown(boost::asio::socket_base::shutdown_type::shutdown_both);
        }
    }
    
    void Close() {
        if (Connected()) {
            Shutdown();
            socket_->close();
        }
    }
    
    bool Connected() {
        return socket_->is_open();
    }
    
    bool Available() {
        return socket_->available() > 0;
    }
    
    void Flush() {
        boost::asio::ip::tcp::no_delay optionNoDelay(true);
        boost::asio::ip::tcp::no_delay optionDelay(false);
        socket_->set_option(optionNoDelay);
        socket_->set_option(optionDelay);
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

