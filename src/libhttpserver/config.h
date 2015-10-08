#ifndef RS_LIBHTTPSERVER_CONFIG_H
#define	RS_LIBHTTPSERVER_CONFIG_H

#include <boost/noncopyable.hpp>

namespace rs {
namespace httpserver {

class Config final : private boost::noncopyable {
public:
    const static unsigned MinThreadCount;
    const static unsigned MaxThreadCount;
    const static unsigned ThreadCoreMultiplier;
    
    const static int MaxRequestCount;
    
    const static int HeaderReceiveTimeoutPeriod;
    const static int BodyReceiveTimeoutPeriod;
    const static int KeepAliveTimeout;
    const static int KeepAliveTimeoutGrace;
    const static int KeepAliveTimeoutTotal;
    
    const static int MaxRequestHeaderSize;
    const static int MaxResponseChunkSize;
    
private:
    Config() = delete;
};

}}

#endif	/* RS_LIBHTTPSERVER_CONFIG_H */

