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
    using byte = unsigned char;
    
    class ScopedClose final {
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
        auto bytesSent = socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(&s[0]), s.length()));
        totalBytesSent_ += bytesSent;
        return bytesSent;
    }
    
    std::size_t Send(const byte* buffer, int length) {
        auto bytesSent = socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(buffer), length));
        totalBytesSent_ += bytesSent;
        return bytesSent;
    }
    
    void Shutdown() {
        if (Connected()) {
            boost::system::error_code err;
            socket_->shutdown(boost::asio::socket_base::shutdown_type::shutdown_both, err);
        }
    }
    
    void Close() {
        if (Connected()) {
            Shutdown();

            boost::system::error_code err;
            socket_->close(err);
        }
    }
    
    bool Connected() {
        return socket_->is_open();
    }
    
    bool Available() {
        boost::system::error_code err;
        return socket_->available(err) > 0;
    }
    
    void Flush();
    
    void NoDelay(bool enable);
    
    asio_socket_ptr getAsioSocket() { return socket_; }    
    
    boost::asio::ip::tcp::endpoint getLocalEndpoint() { return socket_->local_endpoint(); }
    boost::asio::ip::tcp::endpoint getRemoteEndpoint() { return socket_->remote_endpoint(); }
    
    long getTotalBytesSent() {
        return totalBytesSent_;
    }
    
    long getTotalBytesReceived() {
        return totalBytesReceived_;
    }
    
private:
    
    Socket(server_ptr server, asio_socket_ptr socket) : 
        server_(server), socket_(socket), defaultReceiveTimeout_(-1), currentReceiveTimeout_(-1),
        totalBytesSent_(0), totalBytesReceived_(0) {
    }
        
    static int getReceiveTimeout(asio_socket_ptr socket);
    static bool setReceiveTimeout(asio_socket_ptr socket, int seconds);

    void setDefaultReceiveTimeout();
    void setCustomReceiveTimeout(int seconds);
    
    bool Peek(int timeout);
    
    server_ptr server_;
    asio_socket_ptr socket_;
    
    int defaultReceiveTimeout_;
    int currentReceiveTimeout_;
    
    long totalBytesSent_;
    long totalBytesReceived_;
};
    
}}

#endif /* RS_LIBHTTPSERVER_SOCKET_H */
