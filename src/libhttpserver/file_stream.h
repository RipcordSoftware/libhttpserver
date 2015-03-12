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

/**
 * An implementation of a stream which reads data from a file on the file system
 * @note
 * Typically web servers do not want to allow clients to read from any path of
 * the file system. To prevent this FileStream will validate the filename passed before
 * the file contents are read. This prevents clients requesting URIs with .. characters
 * which will walk the file system path. It is assumed that the first character passed is
 * the root of the web server.
 */
class FileStream final : public Stream, private boost::noncopyable {
public:
    
    /**
     * Constructs with the stream source set to a file
     * @param filename The name of the file to read from
     * @param validatePath Set to true to validate that the file path does not walk above the path root, for example: ./abc/../../../../etc/passwd
     */
    FileStream(const std::string& filename, bool validatePath = true) : path_(filename), stream_(filename, std::ifstream::binary), 
            position_(0), length_(-1), validatePath_(validatePath) {}

    /**
     * Tests that the filename exists and optionally whether the filename is valid
     * @param filename The filename to test for existance
     * @param validatePath Set to true to validate that the filename does not exceed its root
     * @return True if the file exists and it is valid
     */
    static bool Exists(const std::string& filename, bool validatePath) {
        return boost::filesystem::exists(boost::filesystem::path(filename)) && (!validatePath || ValidatePath(filename));
    }
    
    /**
     * Tests that the filename specified at construction exists
     * @return True if the file exists and that it validates correctly
     */
    bool Exists() {
        return boost::filesystem::exists(path_) && (!validatePath_ || ValidatePath(path_.c_str()));
    }
    
    /**
     * Tests that the filename specified at construction exists
     * @return True if the file exists and that it validates correctly 
     */
    operator bool() {
        return Exists();
    }
    
    /**
     * Gets the last modified time of the file
     * @return The last modified time
     */
    boost::optional<std::time_t> getLastModifiedTime() {
        boost::system::error_code err;
        auto time = boost::filesystem::last_write_time(path_, err);
        return !err ? time : 0;
    }
    
    /**
     * Performs no operation on a readable stream
     */
    virtual void Flush() override {};
    
    /**
     * @copydoc rs::httpserver::Stream::Read()
     */
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override;
    
    /**
     * @throws InvalidStreamOperationException if called since this is a read-only stream
     */
    virtual int Write(const byte* buffer, int offset, int count) override {
        throw InvalidStreamOperationException();
    }

    /**
     * @copydoc rs::httpserver::Stream::getPosition()
     */    
    virtual long getPosition() override {
        return position_;
    }
    
    /**
     * Gets the length of stream, in this case it will be the length of the file
     * @return 
     */
    virtual long getLength() override { 
        if (length_ < 0) {
            length_ = boost::filesystem::file_size(path_);
        }
        
        return length_;
    }
    
    /**
     * Validates that a given path does not exceed its route
     * @param path The path to test
     * @return True if the path is valid
     */
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

