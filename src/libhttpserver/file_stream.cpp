#include "file_stream.h"

int rs::httpserver::FileStream::Read(byte* buffer, int offset, int count, bool peek) {
        int bytes = 0;
        
        if (stream_) {
            stream_.read(reinterpret_cast<std::ifstream::char_type*>(buffer + offset), count);
            
            bytes = stream_ ? count : stream_.gcount();
            if (bytes > 0) {
                if (peek) {
                    stream_.seekg(-bytes, std::ios_base::cur);
                } else {
                    position_ += bytes;
                }
            }
        }
        
        return bytes;
    }

bool rs::httpserver::FileStream::ValidatePath(const std::string& uri) {
    std::string tempUri(uri);
    
    int index = 0;
    while ((index = tempUri.find("%2e")) != std::string::npos) {
        tempUri.replace(index, 3, ".");
    }
    
    while ((index = tempUri.find("%2E")) != std::string::npos) {
        tempUri.replace(index, 3, ".");
    }
    
    bool validated = tempUri.find("..") == std::string::npos;
    if (!validated) {
        while ((index = tempUri.find("%2f")) != std::string::npos) {
            tempUri.replace(index, 3, "/");
        }
        
        while ((index = tempUri.find("%2F")) != std::string::npos) {
            tempUri.replace(index, 3, "/");
        }
        
        validated = ValidatePathDepth(tempUri);
    }
    
    return validated;
}

bool rs::httpserver::FileStream::ValidatePathDepth(const std::string& uri) {
    auto depth = 0;
    
    if (uri.length() > 1) {
        for (auto  i = uri.find("/", 1); depth >= 0 && i != std::string::npos; i = uri.find("/", i + 1)) {
            if (i > 3 && uri[i - 1] == '.' && uri[i - 2] == '.' && uri[i - 3] == '/') {
                depth--;
            }
            else {
                depth++;
            }
        }
    }
    
    return depth >= 0;
}