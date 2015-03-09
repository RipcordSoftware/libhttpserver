#ifndef RS_LIBHTTPSERVER_MIMETYPES_H
#define	RS_LIBHTTPSERVER_MIMETYPES_H

#include <unordered_map>
#include <string>

#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

namespace rs {
namespace httpserver {

class MimeTypes {
public:
    class Item {
    public:
        Item(const std::string& type, bool compress = true) : type_(type), compress_(compress) {            
        }

        const std::string& getType() {
            return type_;
        }
        
        const bool getCompressible() {
            return compress_;
        }
        
    private:
        std::string type_;
        bool compress_;
    };
    
    static boost::optional<Item> GetType(const char* extn);
    static boost::optional<Item> GetType(const std::string& extn);
    static boost::optional<Item> GetType(const boost::filesystem::path& path);
    
    static bool AddType(const std::string& extn, const std::string& type, bool compress = true);
    static void RemoveType(const std::string& extn);
    
private:
    MimeTypes() {}
    
    static std::unordered_map<std::string, Item> lookup_;
    
};

}}

#endif	/* RS_LIBHTTPSERVER_MIMETYPES_H */

