#ifndef RS_LIBHTTPSERVER_REQUEST_HEADERS_H
#define	RS_LIBHTTPSERVER_REQUEST_HEADERS_H

#include <map>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/make_shared.hpp>

#include "header_buffer.h"
#include "types.h"
#include "header_key_comparer.h"
#include "headers.h"

namespace rs {
namespace httpserver {

class RequestHeaders final : public boost::enable_shared_from_this<RequestHeaders>, private boost::noncopyable {
public:
    using range_index = long;
    using byte_range_collection = std::vector<std::pair<range_index, range_index>>;
    static const range_index RANGE_END;
    
    static request_headers_ptr Create(HeaderBuffer& buffer);
    
    const std::string& getMethod() const {
        return method_;
    }
    
    const std::string& getUri() const {
        return uri_;
    }
    
    const std::string& getRawUri() const {
        return rawUri_;
    }
    
    const std::string& getQueryString() const {
        return queryString_;
    }
    
    const std::string& getVersion() const {
        return version_;
    }
    
    const std::string& getHeader(const std::string& field) const {
        auto value = headers_.find(field);
        return value != headers_.cend() ? value->second : emptyValue_;
    }
    
    const std::string& getContentType() const {
        return getHeader(Headers::ContentType);
    }
    
    const std::string& getAcceptEncoding() const {
        return getHeader(Headers::AcceptEncoding);
    }
    
    const std::string& getAccept() const {
        return getHeader(Headers::Accept);
    }
    
    const std::string& getHost() const {
        return getHeader(Headers::Host);
    }
    
    const std::string& getTransferEncoding() const {
        return getHeader(Headers::TransferEncoding);
    }
    
    const std::string& getContentEncoding() const {
        return getHeader(Headers::ContentEncoding);
    }
    
    const std::string& getExpect() const {
        return getHeader(Headers::Expect);
    }
    
    const std::string& getUserAgent() const {
        return getHeader(Headers::UserAgent);
    }
    
    const std::string& getConnection() const {
        return getHeader(Headers::Connection);
    }
    
    const std::string& getIfNoneMatch() const {
        return getHeader(Headers::IfNoneMatch);
    }
    
    const std::string& getIfModifiedSince() const {
        return getHeader(Headers::IfModifiedSince);
    }
    
    const std::string& getRange() const {
        return getHeader(Headers::Range);
    }
    
    byte_range_collection getByteRanges();

    int getContentLength() const {
        if (contentLength_ < 0) {
            contentLength_ = 0;
            
            auto contentLengthValue = getHeader(Headers::ContentLength);
            if (contentLengthValue.length() > 0) {
                contentLength_ = boost::lexical_cast<int>(contentLengthValue);
            }
        }
        return contentLength_;
    }
    
    bool IsChunked() const {
        auto& encoding = getTransferEncoding();
        return encoding.length() > 0 ? boost::iequals(encoding, "chunked") : false;
    }
    
private:
    friend boost::shared_ptr<RequestHeaders> boost::make_shared<RequestHeaders>();
    
    typedef std::map<std::string, std::string, HeaderKeyComparer> headers;
    
    RequestHeaders() : contentLength_(-1) {}

    void GetHeaders(const HeaderBuffer& buffer, int headersLength);
    
    static std::string UriDecode(const std::string&);
    static unsigned GetDigitValue(char ch);
    
    std::string method_;
    std::string version_;
    std::string uri_;
    std::string rawUri_;    
    std::string queryString_;
    mutable int contentLength_;        
    
    headers headers_;
    
    static const std::string emptyValue_;
    static const char endOfLine_[];
};

}}

#endif	/* RS_LIBHTTPSERVER_REQUEST_HEADERS_H */