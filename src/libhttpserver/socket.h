#ifndef RS_LIBHTTPSERVER_SOCKET_H
#define	RS_LIBHTTPSERVER_SOCKET_H

#include <vector>
#include <functional>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
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
    
    static socket_ptr Create(service_ptr service) {
        return Create(service, nullptr);
    }
    
    void Listen(const std::string& host, int port, boost::function<void (socket_ptr, const boost::system::error_code &)> func);
       
    std::size_t Read(buffer& b) {
        return socket_->receive(boost::asio::mutable_buffers_1(static_cast<void*>(&b[0]), b.size()));
    }
    
    std::size_t Send(const std::string& s) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const std::string::value_type*>(&s[0]), s.size() * sizeof(std::string::value_type)));
    }
    
    std::size_t Send(const buffer& b) {
        return socket_->send(boost::asio::const_buffers_1(static_cast<const void*>(&b[0]), b.size()));
    }
    
    boost::asio::ip::tcp::endpoint getLocalEndpoint() { return socket_->local_endpoint(); }
    boost::asio::ip::tcp::endpoint getRemoteEndpoint() { return socket_->remote_endpoint(); }
    
private:
    
    Socket(service_ptr service, boost::shared_ptr<boost::asio::ip::tcp::socket> socket, std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor = nullptr) : 
        service_(service), socket_(socket), acceptor_(acceptor) {}
        
    static socket_ptr Create(service_ptr service, std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor);
        
    void StartAccept(boost::function<void (socket_ptr, const boost::system::error_code &)> func);
    static void HandleAccept(socket_ptr socket, boost::function<void (socket_ptr, const boost::system::error_code &)> func, const boost::system::error_code& error);
            
    service_ptr service_;
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
    
};
    
}}

#endif	/* RS_LIBHTTPSERVER_SOCKET_H */

