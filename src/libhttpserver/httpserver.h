#ifndef RS_LIBHTTPSERVER_HTTPSERVER_H
#define	RS_LIBHTTPSERVER_HTTPSERVER_H

#include <string>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "types.h"
#include "config.h"

namespace rs {
namespace httpserver {
    
class RequestRouter;

class HttpServer final : public boost::enable_shared_from_this<HttpServer>, private boost::noncopyable {
public:
    typedef boost::function<void (socket_ptr, request_ptr, response_ptr)> RequestCallback;
    typedef boost::function<bool (socket_ptr, request_ptr)> Request100ContinueCallback;
    
    static server_ptr Create(const std::string& host, int port, int threads = EstimateThreadPoolSize()) {
        return server_ptr(new HttpServer(host, port, threads));
    }
    
    ~HttpServer();
    
    void Start(const RequestRouter& router, RequestCallback requestCallback);
    void Start(const RequestRouter& router, RequestCallback requestCallback, Request100ContinueCallback requestContinueCallback);
    void Start(RequestCallback requestCallback);
    void Start(RequestCallback requestCallback, Request100ContinueCallback requestContinueCallback);
    
    static int EstimateThreadPoolSize() {
        auto cores = boost::thread::hardware_concurrency();
        auto threads = std::max(cores * Config::ThreadCoreMultiplier, Config::MinThreadCount);
        return std::min(threads, Config::MaxThreadCount);
    }
    
private:
    HttpServer(const std::string& host, int port, int threads);
    
    void StartAccept(socket_ptr socket);
    void HandleAccept(socket_ptr socket, const boost::system::error_code& error);    
    void HandleRequest(socket_ptr socket);
    void HandleStop();
    
    static bool DefaultRequestContinueCallback(socket_ptr, request_ptr);
    
    static void SendRequestTimeout(socket_ptr);
    static void SendBadRequest(socket_ptr);
    static void SendInternalServerError(socket_ptr);
    
    const std::string host_;
    const int port_;
    const int threads_;
    
    boost::asio::io_service service_;
    boost::asio::signal_set signals_;
    boost::asio::ip::tcp::acceptor acceptor_;
    
    RequestCallback requestCallback_;
    Request100ContinueCallback requestContinueCallback_;
};

}}

#endif	/* RS_LIBHTTPSERVER_HTTPSERVER_H */