#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "httpserver.h"
#include "socket.h"
#include "request_headers.h"
#include "request.h"
#include "response.h"
#include "exceptions.h"
#include "request_router.h"

rs::httpserver::HttpServer::HttpServer(const std::string& host, int port, int threads) : 
        host_(host), port_(port), threads_(threads), service_(),
        acceptor_(service_), signals_(service_) {
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
    signals_.add(SIGQUIT);
    signals_.async_wait(boost::bind(&HttpServer::HandleStop, this));
}

rs::httpserver::HttpServer::~HttpServer() {
}

void rs::httpserver::HttpServer::HandleStop() {        
    service_.stop();
}

void rs::httpserver::HttpServer::Start(const RequestRouter& router, RequestCallback requestCallback) {
    Start([&](socket_ptr socket, request_ptr request, response_ptr response) {
        if (!router.Match(request, response) && requestCallback) {            
            requestCallback(socket, request, response);
        }
    });
}

void rs::httpserver::HttpServer::Start(RequestCallback requestCallback) {
    Start(requestCallback, [](socket_ptr, request_ptr){ return true; });
}

void rs::httpserver::HttpServer::Start(RequestCallback requestCallback, Request100ContinueCallback request_continue_callback) {
    auto addr = boost::asio::ip::address::from_string(host_);
    boost::asio::ip::tcp::endpoint ep(addr, port_);
    
    asio_socket_ptr asio_socket(new boost::asio::ip::tcp::socket(service_));    
    auto socket = Socket::Create(shared_from_this(), asio_socket);
    
    requestCallback_ = requestCallback;
    requestContinueCallback_ = request_continue_callback;
    
    acceptor_.open(ep.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(ep);
    acceptor_.listen();
    StartAccept(std::move(socket));
    
    boost::thread_group workers;
    for (auto i = 0; i < threads_; ++i) {
        workers.create_thread(boost::bind(&boost::asio::io_service::run, &service_));
    }
    workers.join_all();
}

void rs::httpserver::HttpServer::StartAccept(socket_ptr socket) {
    acceptor_.async_accept(*socket->getAsioSocket(), boost::bind(&HttpServer::HandleAccept, this, socket, boost::asio::placeholders::error));
}

void rs::httpserver::HttpServer::HandleAccept(socket_ptr socket, const boost::system::error_code& error) {
    if (error) {
        // TODO: do something more useful with this
        std::cout << error.message() << std::endl;
    }
    else {
        asio_socket_ptr new_asio_socket(new boost::asio::ip::tcp::socket(service_));
        auto new_socket = Socket::Create(shared_from_this(), new_asio_socket);    
        StartAccept(std::move(new_socket));    

        HandleRequest(socket);
    }
}

void rs::httpserver::HttpServer::HandleRequest(socket_ptr socket) {
    Socket::ScopedClose close(socket);
    HeaderBuffer headerBuffer(Config::MaxRequestHeaderSize);
    auto responseCount = 0;
    
    try {    
        while (socket->Connected() && responseCount < Config::MaxResponseCount) {
            auto headerReceiveTimeout = headerBuffer.getDataLength() > 0 ? Config::HeaderReceiveTimeoutPeriod : Config::KeepAliveTimeoutTotal;

            auto responseBytes = headerBuffer.Receive(socket, headerReceiveTimeout);
            if (responseBytes <= 0) {
                throw HeaderTimeoutException();
            }
            
            auto requestHeaders = RequestHeaders::Create(headerBuffer);            
            if (!!requestHeaders) {
                auto request = Request::Create(socket, requestHeaders, headerBuffer);
                auto response = Response::Create(socket, request);
                
                // TODO: implement 100-continue logic
                //requestContinueCallback_(socket, request);
                
                requestCallback_(socket, request, response);
                
                if (!response->HasResponded()) {
                    response->ResetHeaders().setStatusCode(404).setStatusDescription("Not found").Send();
                }
                
                headerBuffer.Reset();
                ++responseCount;
                
                if (response->ShouldClose()) {
                    socket->Close();
                }
            } else if (headerBuffer.IsFull()) {
                throw HeaderSizeException();
            }
        }
    } catch (const HeaderTimeoutException&) {
        ;
    } catch (const HttpServerException& e) {
        // TODO: do something more useful with this
        std::cout << "ERROR: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // TODO: do something more useful with this
        std::cout << "ERROR: " << e.what() << std::endl;
    } catch (...) {
        // TODO: do something more useful with this
        std::cout << "ERROR: something bad happened!" << std::endl;
        throw;
    }
}