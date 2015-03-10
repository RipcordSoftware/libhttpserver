#ifndef RS_LIBHTTPSERVER_HEADER_KEY_COMPARER_H
#define	RS_LIBHTTPSERVER_HEADER_KEY_COMPARER_H

#include <string>

namespace rs {
namespace httpserver {
 
struct HeaderKeyComparer {
    bool operator()(const std::string& x, const std::string& y) const {
        auto diff = 0;
        auto px = x.c_str();
        auto py = y.c_str();
        do {
            diff = (*px | 0x20) - (*py | 0x20);
        } while (diff == 0 && *px++ != '\0' && *py++ != '\0');

        return diff < 0;
    }
};
    
}}

#endif	/* RS_LIBHTTPSERVER_HEADER_KEY_COMPARER_H */

