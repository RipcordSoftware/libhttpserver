#ifndef RS_LIBHTTPSERVER_FILE_STREAM_H
#define	RS_LIBHTTPSERVER_FILE_STREAM_H

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>

#include "stream.h"

namespace rs {
namespace httpserver {
    
class FileStream final : public Stream, private boost::noncopyable {
public:
    
    FileStream(const std::string& filename) : path_(filename), stream_(filename, std::ifstream::binary), position_(0), length_(-1) {}

    static bool Exists(const std::string& filename) {
        return boost::filesystem::exists(boost::filesystem::path(filename));
    }
    
    bool Exists() {
        return boost::filesystem::exists(path_);
    }
    
    operator bool() {
        return Exists();
    }
    
    virtual void Flush() override {};
    
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override {
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
    
    virtual int Write(const byte* buffer, int offset, int count) override {
        throw InvalidStreamOperationException();
    }
    
    virtual long getPosition() override {
        return position_;
    }
    
    virtual long getLength() override { 
        if (length_ < 0) {
            length_ = boost::filesystem::file_size(path_);
        }
        
        return length_;
    }
    
private:
    
    const boost::filesystem::path path_;
    std::ifstream stream_;
    long position_;
    long length_;
};
    
}}


#endif	/* RS_LIBHTTPSERVER_FILE_STREAM_H */

