#include "mime_types.h"

std::vector<rs::httpserver::MimeTypes::Item> rs::httpserver::MimeTypes::items_ = {
    { ".txt", "text/plain" },
    { ".htm", "text/html" },
    { ".html", "text/html" },
    { ".css", "text/css" },
    { ".js", "text/javascript" },
    { ".csv", "text/csv" },
    { ".rtf", "text/rtf" },
    { ".xml", "text/xml" },
    { ".png", "image/png", false },
    { ".jpg", "image/jpg", false },
    { ".jpeg", "image/jpg", false },
    { ".gif", "image/gif", false },
    { ".ico", "image/ico" },
    { ".woff", "application/font-woff", false },
    { ".woff2", "application/font-woff2", false },
    { ".eot", "application/vnd.ms-fontobject", false },
    { ".ttf", "application/x-font-ttf" },
    { ".otf", "application/x-font-opentype" },
    { ".svg", "image/svg+xml" },
    { ".json", "application/json" },
    { ".pdf", "application/pdf", false },
    { ".ps", "application/postscript" },
    { ".zip", "application/zip", false },
    { ".gz", "application/gzip", false }
};

rs::httpserver::MimeTypes::item_lookup_type rs::httpserver::MimeTypes::itemLookup_(rs::httpserver::MimeTypes::items_.cbegin(), rs::httpserver::MimeTypes::items_.cend());

rs::httpserver::MimeTypes::extension_lookup_type rs::httpserver::MimeTypes::extnLookup_(rs::httpserver::MimeTypes::items_.cbegin(), rs::httpserver::MimeTypes::items_.cend());

boost::optional<const rs::httpserver::MimeTypes::Item&> rs::httpserver::MimeTypes::GetExtensionType(const char* extn) {
    return GetExtensionType(std::string(extn));
}

boost::optional<const rs::httpserver::MimeTypes::Item&> rs::httpserver::MimeTypes::GetContentType(const char* type) {
    return GetContentType(std::string(type));
}

boost::optional<const rs::httpserver::MimeTypes::Item&> rs::httpserver::MimeTypes::GetExtensionType(const std::string& extn) {
    if (extn.length() > 0) {    
        if (extn[0] != '.') {
            auto index = extn.rfind(".");
            if (index != std::string::npos) {
                return GetExtensionType(std::string(std::string(&extn[index])));
            }
        }
        
        auto iter = extnLookup_.find(Item{extn, ""});
        if (iter != extnLookup_.cend()) {
            return *iter;
        } 
    }
    
    return boost::optional<const Item&>();
}

boost::optional<const rs::httpserver::MimeTypes::Item&> rs::httpserver::MimeTypes::GetContentType(const std::string& type) {
    auto iter = itemLookup_.find(Item{"", type});
    if (iter != itemLookup_.cend()) {
        return *iter;
    }
    
    return boost::optional<const Item&>();
}

boost::optional<const rs::httpserver::MimeTypes::Item&> rs::httpserver::MimeTypes::GetExtensionType(const boost::filesystem::path& path) {
    auto extn = path.extension();
    if (!extn.empty()) {
        return GetExtensionType(std::string(path.c_str()));
    } else {
        return boost::optional<const Item&>();
    }    
}

bool rs::httpserver::MimeTypes::AddType(const std::string& extn, const std::string& type, bool compress) {
    itemLookup_.erase(Item{"", type});
    extnLookup_.erase(Item{extn, ""});
    return extnLookup_.emplace(extn, type, compress).second && itemLookup_.emplace(extn, type, compress).second;
}

void rs::httpserver::MimeTypes::RemoveExtensionType(const std::string& extn) {
    auto item = GetExtensionType(extn);
    if (item.is_initialized()) {
        itemLookup_.erase(item.get());
        extnLookup_.erase(item.get());
    }
}