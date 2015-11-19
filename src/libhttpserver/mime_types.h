#ifndef RS_LIBHTTPSERVER_MIMETYPES_H
#define	RS_LIBHTTPSERVER_MIMETYPES_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

namespace rs {
namespace httpserver {

class MimeTypes final {
public:
    class Item {
    public:
        class ItemTypeHash final {
        public:
            std::size_t operator()(const Item& item) const {
                std::hash<decltype(item.type_)> hash;
                return hash(item.type_);
            }
        };
        
        class ItemExtensionHash final {
        public:
            std::size_t operator()(const Item& item) const {
                std::hash<decltype(item.extn_)> hash;
                return hash(item.extn_);
            }
        };
        
        class ItemTypeEquals final {
        public:
            bool operator()(const Item& lhs, const Item& rhs) const {
                return lhs.type_ == rhs.type_;
            }
        };
        
        class ItemExtensionEquals final {
        public:
            bool operator()(const Item& lhs, const Item& rhs) const {
                return lhs.extn_ == rhs.extn_;
            }
        };
        
        Item(const std::string extn, const std::string& type, bool compress = true) : extn_(extn), type_(type), compress_(compress) {            
        }

        const std::string& getType() const {
            return type_;
        }
        
        const bool getCompressible() const {
            return compress_;
        }
                
        static bool getTypeEqual(const Item& lhs, const Item& rhs);
        
    private:
        std::string extn_;
        std::string type_;
        bool compress_;
    };
    
    MimeTypes() = delete;
    
    static boost::optional<const Item&> GetExtensionType(const char* extn);
    static boost::optional<const Item&> GetExtensionType(const std::string& extn);
    static boost::optional<const Item&> GetExtensionType(const boost::filesystem::path& path);
    
    static boost::optional<const Item&> GetContentType(const char* type);
    static boost::optional<const Item&> GetContentType(const std::string& type);
    
    static bool AddType(const std::string& extn, const std::string& type, bool compress = true);
    static void RemoveExtensionType(const std::string& extn);
    
private:
    using item_lookup_type = std::unordered_set<Item, Item::ItemTypeHash, Item::ItemTypeEquals>;
    using extension_lookup_type = std::unordered_set<Item, Item::ItemExtensionHash, Item::ItemExtensionEquals>;
    
    static std::vector<Item> items_;
    static extension_lookup_type extnLookup_;
    static item_lookup_type itemLookup_;    
};

}}

#endif	/* RS_LIBHTTPSERVER_MIMETYPES_H */

