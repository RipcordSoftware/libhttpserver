#ifndef RS_LIBHTTPSERVER_REQUEST_ROUTER_H
#define RS_LIBHTTPSERVER_REQUEST_ROUTER_H

#include <boost/regex.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>

#include <vector>
#include <map>
#include <cstring>

#include "types.h"

namespace rs {
namespace httpserver {

/**
 * A class that routes requests to a handler based on the method/uri
 */
class RequestRouter final {
public:
    struct CallbackArgsKeyComparer {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) < 0;
        }
    };
    
    typedef std::map<const char*, const char*, CallbackArgsKeyComparer> CallbackArgs;
    typedef boost::function<bool(request_ptr request, const CallbackArgs&, response_ptr response)> Callback;
    
    RequestRouter();
    
    /**
     * Adds a new method/regex pair into the router
     */
    void Add(const char* method, const char* re, Callback func);        
    
    /**
     * Matches the request against the routes and invokes the associated callback if one is found
     * @return true if the request was handled
     */
    bool Match(request_ptr request, response_ptr response) const;
    
private:
    std::map<std::string, std::vector<std::tuple<boost::basic_regex<char>, Callback, std::vector<std::string>>>> routes_;
};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_ROUTER_H */