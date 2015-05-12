#ifndef RS_LIBHTTPSERVER_READABLE_STRING_STREAM_H
#define	RS_LIBHTTPSERVER_READABLE_STRING_STREAM_H

#include <algorithm>

#include <boost/noncopyable.hpp>

#include "stream.h"
#include "exceptions.h"

namespace rs {
namespace httpserver {
    
/**
 * A readable stream containing string data
 */
class ReadableStringStream final : public Stream, private boost::noncopyable {
public:
    /**
     * Constructs the stream containing the string data specified
     * @param data The string data to populate the stream with
     */
    ReadableStringStream(const std::string& data) : data_(data), position_(0) {}
    
    /**
     * Performs no operation on a readable stream
     */
    virtual void Flush() override {};
    
    /** 
     * @copydoc rs::httpserver::Stream::Read()
     */
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override {       
        int bytes = 0;
        
        if (position_ < data_.length()) {
            auto data = reinterpret_cast<const byte*>(data_.c_str());
            if (data != nullptr) {
                int length = data_.length();
                bytes = std::min(count, length - position_);
                std::copy(data + position_, data + position_ + bytes, buffer + offset);

                if (!peek) {
                    position_ += bytes;
                }
            }
        }
        
        return bytes;
    }
    
    /**
     * @throws InvalidStreamOperationException if called since this is a read-only stream
     */
    virtual int Write(const byte* buffer, int offset, int count) override {
        throw InvalidStreamOperationException();
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
     * Appends new string data to the stream. Will modify the length of the stream but not the position in the stream.
     * @param data The new string data to add
     */
    void AppendData(const std::string& data) {
        data_ += data;
    }
    
private:
    std::string data_;
    int position_;
};

}}

#endif	/* RS_LIBHTTPSERVER_READABLE_STRING_STREAM_H */
