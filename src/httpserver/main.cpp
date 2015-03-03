#include <iostream>
#include <vector>

#include "../libhttpserver/libhttpserver.h"

using namespace std;

template <typename TElem>
ostream& operator<<(ostream& os, const vector<TElem>& vec) {
    typedef typename vector<TElem>::const_iterator iter_t;
    const iter_t iter_begin = vec.cbegin();
    const iter_t iter_end   = vec.cend();
    os << "[";
    for (iter_t iter = iter_begin; iter != iter_end; ++iter) {
        os << ((iter != iter_begin) ? "," : "") << *iter;
    }
    os << "]";
    return os;
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024, 8);
    
    auto func = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request) {
        auto remote = socket->getRemoteEndpoint();

        stringstream html;
        html << "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<html><body>" <<
            "<div>hello to " << remote.address().to_string() << ":" << remote.port() <<
            " from " << request->getHeaders()->getHost() << 
            " at uri " << request->getHeaders()->getUri() << "</div>" <<
            "<div>Query string: " << request->getQueryString().getKeys() << "</div>" <<
            "</body></html>";

        socket->Send(html.str());
        
        return true;
    };

    server->Start(func);
    
    return 0;
}