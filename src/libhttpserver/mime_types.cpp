#include "mime_types.h"

std::unordered_map<std::string, rs::httpserver::MimeTypes::Item> rs::httpserver::MimeTypes::lookup_ = { 
    { ".txt", { "text/plain" } },
    { ".htm", { "text/html" } },
    { ".html", { "text/html" } },
    { ".css", { "text/css" } },
    { ".js", { "text/javascript" } },
    { ".csv", { "text/csv" } },
    { ".rtf", { "text/rtf" } },
    { ".xml", { "text/xml" } },
    { ".png", { "image/png", false } },
    { ".jpg", { "image/jpeg", false } },
    { ".jpeg", { "image/jpg", false } },
    { ".gif", { "image/gif", false } },
    { ".ico", { "image/ico" } },    
    { ".woff", { "application/font-woff", false } },
    { ".svg", { "image/svg+xml" } },
    { ".json", { "application/json" } },
    { ".pdf", { "application/pdf", false } },
    { ".ps", { "application/postscript" } },
    { ".zip", { "application/zip", false } },
    { ".gz", { "application/gzip", false } }
};

boost::optional<rs::httpserver::MimeTypes::Item> rs::httpserver::MimeTypes::GetType(const char* extn) {
    return GetType(std::string(extn));
}

boost::optional<rs::httpserver::MimeTypes::Item> rs::httpserver::MimeTypes::GetType(const std::string& extn) {
    if (extn.length() > 0) {    
        if (extn[0] != '.') {
            auto index = extn.rfind(".");
            if (index != std::string::npos) {
                return GetType(std::string(std::string(&extn[index])));
            }
        }
        
        auto iter = lookup_.find(extn);
        if (iter != lookup_.cend()) {
            return iter->second;
        } 
    }
    
    return boost::optional<Item>();
}

boost::optional<rs::httpserver::MimeTypes::Item> rs::httpserver::MimeTypes::GetType(const boost::filesystem::path& path) {
    auto extn = path.extension();
    if (!extn.empty()) {
        return GetType(std::string(path.c_str()));
    } else {
        return boost::optional<Item>();
    }    
}

bool rs::httpserver::MimeTypes::AddType(const std::string& extn, const std::string& type, bool compress) {
    lookup_.erase(extn);
    return lookup_.emplace(extn, Item(type, compress)).second;
}

void rs::httpserver::MimeTypes::RemoveType(const std::string& extn) {
    lookup_.erase(extn);
}