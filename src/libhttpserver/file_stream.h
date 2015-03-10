#ifndef RS_LIBHTTPSERVER_FILE_STREAM_H
#define	RS_LIBHTTPSERVER_FILE_STREAM_H

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

#include "stream.h"
#include "exceptions.h"

namespace rs {
namespace httpserver {
    
class FileStream final : public Stream, private boost::noncopyable {
public:
    
    FileStream(const std::string& filename, bool validatePath = true) : path_(filename), stream_(filename, std::ifstream::binary), 
            position_(0), length_(-1), validatePath_(validatePath) {}

    static bool Exists(const std::string& filename, bool validatePath) {
        return boost::filesystem::exists(boost::filesystem::path(filename)) && (!validatePath || ValidatePath(filename));
    }
    
    bool Exists() {
        return boost::filesystem::exists(path_) && (!validatePath_ || ValidatePath(path_.c_str()));
    }
    
    operator bool() {
        return Exists();
    }
    
    boost::optional<std::time_t> getLastModifiedTime() {
        boost::system::error_code err;
        auto time = boost::filesystem::last_write_time(path_, err);
        return !err ? time : 0;
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
    
    const bool validatePath_;
};
    
}}


#endif	/* RS_LIBHTTPSERVER_FILE_STREAM_H */

