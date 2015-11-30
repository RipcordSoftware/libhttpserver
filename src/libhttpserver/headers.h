#ifndef RS_LIBHTTPSERVER_HEADERS_H
#define	RS_LIBHTTPSERVER_HEADERS_H

#include <string>

namespace rs {
namespace httpserver {

class Headers final {
public:
    static const std::string Http10;
    static const std::string Http11;
    
    static const int DefaultStatusCode;
    static const std::string DefaultStatusDescription;
    static const std::string DefaultVersion;
    
    static const std::string Get;
    static const std::string Post;
    static const std::string Put;
    static const std::string Head;
    static const std::string Delete;        
    
    static const std::string ContentLength;
    static const std::string ContentType;    
    static const std::string Accept;
    static const std::string AcceptEncoding;
    static const std::string ContentEncoding;
    static const std::string ContentDisposition;
    static const std::string TransferEncoding;
    static const std::string Expect;
    static const std::string UserAgent;
    static const std::string Host;
    static const std::string Connection;
    static const std::string KeepAlive;
    static const std::string Location;
    static const std::string LastModified;
    static const std::string ETag;
    static const std::string IfNoneMatch;
    static const std::string IfModifiedSince;
    static const std::string CacheControl;
    static const std::string Pragma;
    static const std::string Range;
    static const std::string ContentRange;
};

}}

#endif	/* RS_LIBHTTPSERVER_HEADERS_H */

