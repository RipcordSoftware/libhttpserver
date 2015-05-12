#ifndef RS_LIBHTTPSERVER_WRITABLE_STRING_STREAM_H
#define	RS_LIBHTTPSERVER_WRITABLE_STRING_STREAM_H

#include <boost/noncopyable.hpp>

#include "stream.h"
#include "exceptions.h"

namespace rs {
namespace httpserver {
    
 /**
 * A writable stream containing string data
 */
class WritableStringStream final : public Stream, private boost::noncopyable {
public:
    WritableStringStream() : position_(0) {}
    
    /**
     * Performs no operation since there is no backing store
     */
    virtual void Flush() override {};
    
    /** 
     * @throws InvalidStreamOperationException if called since this is a write-only stream
     */
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override {
        throw InvalidStreamOperationException();
    }
    
    /** 
     * @copydoc rs::httpserver::Stream::Write()
     */
    int Write(const char* buffer, int offset, int count) {
       return Write(reinterpret_cast<const byte*>(buffer), offset, count);
    }
    
    /** 
     * @copydoc rs::httpserver::Stream::Write()
     */
    virtual int Write(const byte* buffer, int offset, int count) override {
        int written = 0;
        auto data = reinterpret_cast<const char*>(buffer);
        if (data != nullptr) {
            data_.append(data + offset, count);
            position_ += count;
            written = count;
        }
        
        return written;
    }
    
    /**
     * @copydoc rs::httpserver::Stream::getPosition()
     */
    virtual long getPosition() override { return position_; }
    
    /**
     * Returns the length of the string/stream
     * @return The length of the stream
     */
    virtual long getLength() override { return data_.length(); }
    
    /**
     * Gets the character data in the stream
     * @return The stream data
     */
    const std::string& str() { return data_; }
  
private:
    std::string data_;
    int position_;    
};

}}

#endif	/* RS_LIBHTTPSERVER_WRITABLE_STRING_STREAM_H */

