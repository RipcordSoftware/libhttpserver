#ifndef RS_LIBHTTPSERVER_QUERY_STRING_H
#define	RS_LIBHTTPSERVER_QUERY_STRING_H

#include <string>
#include <map>
#include <vector>

namespace rs {
namespace httpserver {

class QueryString final {
public:
    QueryString(const std::string& data) : data_(data) {}
    
    bool IsKey(const std::string& key) const;
    const std::string& getValue(const std::string& key) const;
    
    std::vector<std::string> getKeys() const;
    
private:
    
    void Parse() const;

    const std::string data_;
    mutable std::map<std::string, std::string> lookup_;
    
    const std::string emptyValue_;
};

}}

#endif	/* RS_LIBHTTPSERVER_QUERY_STRING_H */

