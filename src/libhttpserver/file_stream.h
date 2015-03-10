#ifndef RS_LIBHTTPSERVER_FILE_STREAM_H
#define	RS_LIBHTTPSERVER_FILE_STREAM_H

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>

#include "stream.h"
#include "exceptions.h"

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
    
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override;
    
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
    
    static bool ValidatePath(const std::string& path);        
    
private:
    
    static bool ValidatePathDepth(const std::string& path);
    
    const boost::filesystem::path path_;
    std::ifstream stream_;
    long position_;
    long length_;
};
    
}}


#endif	/* RS_LIBHTTPSERVER_FILE_STREAM_H */

