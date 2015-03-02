#ifndef RS_LIBHTTPSERVER_CONFIG_H
#define	RS_LIBHTTPSERVER_CONFIG_H

#include <boost/noncopyable.hpp>

namespace rs {
namespace httpserver {

class Config final : private boost::noncopyable {
public:
    const static int MaxResponseCount = 100;
    
    const static int ReceiveTimeoutPeriod = 30;    
    const static int KeepAliveTimeout = 10;
    const static int KeepAliveTimeoutGrace = 2;
    const static int KeepAliveTimeoutTotal = KeepAliveTimeout + KeepAliveTimeoutGrace;
    
    const static int MaxRequestHeaderSize = 16384;
    
private:
    Config() = delete;
};

}}

#endif	/* RS_LIBHTTPSERVER_CONFIG_H */

