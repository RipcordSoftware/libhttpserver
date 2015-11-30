#ifndef RS_LIBHTTPSERVER_RESPONSE_HEADERS_H
#define RS_LIBHTTPSERVER_RESPONSE_HEADERS_H

#include <map>
#include <string>

#include "header_key_comparer.h"

namespace rs {
namespace httpserver {
  
using ResponseHeaders = std::map<std::string, std::string, HeaderKeyComparer>;
    
}}

#endif	/* RS_LIBHTTPSERVER_RESPONSE_HEADERS_H */

