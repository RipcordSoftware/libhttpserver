#ifndef RS_LIBHTTPSERVER_STREAM_H
#define	RS_LIBHTTPSERVER_STREAM_H

#include <iostream>
#include <string>

#include "config.h"

namespace rs {
namespace httpserver {

/**
 * The definition of a stream
 */
class Stream {
public:
    Stream() {}
    Stream(const Stream&) = delete;
    Stream& operator=(const Stream&) = delete;
    
    typedef unsigned char byte;
    
    /**
     * Flushes any pending written bytes on the stream. Performs no operation
     * if the stream is read-only
     */
    virtual void Flush() = 0;
    
    /**
     * Reads any pending bytes on the stream
     * @param buffer the buffer to read into
     * @param offset the offset in the buffer where the read data will be placed
     * @param count the maximum numbers of bytes to read
     * @param peek when true reads from the stream without moving the current read position
     * @return the number of bytes read or zero if there were no bytes available
     */
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) = 0;
    
    /**
     * Writes buffer data to the stream
     * @param buffer the buffer to write from
     * @param offset the offset in the buffer where the written data will start
     * @param count the number of bytes to write
     * @return the number of bytes written
     */
    virtual int Write(const byte* buffer, int offset, int count) = 0;
    
    /**
     * Gets the current position in the stream
     * @return the position in the stream
     */
    virtual long getPosition() = 0;
    
    /**
     * Gets the length of the stream if known
     * @return the length of the stream
     */
    virtual long getLength() = 0;
    
    /**
     * Copies the contents of one stream to another
     * @param inStream the source stream to read from
     * @param outStream the destination stream to write to
     */
    static void Copy(Stream& inStream, Stream& outStream) {
        int bytesRead = 0;
        byte buffer[2048];
        while ((bytesRead = inStream.Read(buffer, 0, sizeof(buffer))) > 0) {
            outStream.Write(buffer, 0, bytesRead);
        }
    }
    
    /**
     * Copies the contents of one stream to another
     * @param inStream the source stream to read from
     * @param outStream the destination stream to write to
     */
    static void Copy(std::iostream& inStream, Stream& outStream) {
        inStream.seekg(0);
        
        byte buffer[2048];
        while (inStream) {
            inStream.read(reinterpret_cast<std::iostream::char_type*>(buffer), sizeof(buffer));
            outStream.Write(buffer, 0, inStream.gcount());
        }
    }
    
    static int Write(Stream& stream, const char* buffer, int offset, int count) {
        return stream.Write(reinterpret_cast<const byte*>(buffer), offset, count);
    }
    
    static int Write(Stream& stream, std::string buffer) {
        return stream.Write(reinterpret_cast<const byte*>(buffer.c_str()), 0, buffer.size());
    }
};

}}

#endif	/* RS_LIBHTTPSERVER_STREAM_H */

