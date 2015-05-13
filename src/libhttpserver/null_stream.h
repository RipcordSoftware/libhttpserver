#ifndef RS_LIBHTTPSERVER_NULL_STREAM_H
#define	RS_LIBHTTPSERVER_NULL_STREAM_H

#include "stream.h"

namespace rs {
namespace httpserver {

/**
 * An empty stream
 */
class NullStream : public Stream {
public:

    /**
     * Performs a no-op
     */
    virtual void Flush() override {}
    
    /**
     * Reads any pending bytes on the stream
     * @return always returns 0
     */
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) override {
        return 0;
    }
    
    /**
     * Writes buffer data to the stream
     * @return always returns 0
     */
    virtual int Write(const byte* buffer, int offset, int count) override {
        return 0;
    }
    
    /**
     * Gets the current position in the stream
     * @return always returns 0
     */
    virtual long getPosition() override {
        return 0;
    }
    
    /**
     * Gets the length of the stream if known
     * @return always returns 0
     */
    virtual long getLength() override {
        return 0;
    }    
};

}}

#endif	/* RS_LIBHTTPSERVER_NULL_STREAM_H */

