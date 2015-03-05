#ifndef RS_LIBHTTPSERVER_STREAM_H
#define	RS_LIBHTTPSERVER_STREAM_H

namespace rs {
namespace httpserver {

class Stream {
public:
    typedef unsigned char byte;
    
    virtual void Flush() = 0;
    virtual int Read(byte* buffer, int offset, int count, bool peek = false) = 0;
    virtual int Write(const byte* buffer, int offset, int count) = 0;
    virtual long getPosition() = 0;
    virtual long getLength() = 0;
    
    static void Copy(Stream& inStream, Stream& outStream) {
        int bytesRead = 0;
        byte buffer[2048];
        while ((bytesRead = inStream.Read(buffer, 0, sizeof(buffer))) > 0) {
            outStream.Write(buffer, 0, bytesRead);
        }
    }
};

}}

#endif	/* RS_LIBHTTPSERVER_STREAM_H */

