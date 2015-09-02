#ifndef RS_LIBHTTPSERVER_SOCKET_TIMEVAL_OPTION_H
#define RS_LIBHTTPSERVER_SOCKET_TIMEVAL_OPTION_H

#include <sys/time.h>

namespace rs {
namespace httpserver {

// based on: http://stackoverflow.com/questions/292997/can-you-set-so-rcvtimeo-and-so-sndtimeo-socket-options-in-boost-asio
template <int Level, int Name>
class SocketTimevalOption final {
public:

    SocketTimevalOption() : value_(zero_timeval()) {}
    
    explicit SocketTimevalOption(int seconds, int microseconds = 0) : value_({.tv_sec=seconds, .tv_usec=microseconds}) {}
    
    explicit SocketTimevalOption(const ::timeval& v) : value_(v) {}
    
    ::timeval value() const {
        return value_;
    }
    
    time_t seconds() const {
        return value_.tv_sec;
    }
    
    suseconds_t microseconds() const {
        return value_.tv_usec;
    }
    
    template <typename Protocol>
    int level(const Protocol&) const {
        return Level;
    }
    
    template <typename Protocol>
    int name(const Protocol&) const {
        return Name;
    }
    
    template <typename Protocol>
    ::timeval* data(const Protocol&) {
        return &value_;
    }
    
    template <typename Protocol>
    const ::timeval* data(const Protocol&) const {
        return &value_;
    }
    
    template <typename Protocol>
    std::size_t size(const Protocol&) const {
        return sizeof(value_);
    }
    
    template <typename Protocol>
    void resize(const Protocol&, std::size_t s) {
        if (s != sizeof(value_)) {
            throw std::length_error("timeval socket option resize");
        }
    }
    
private:
    
    static ::timeval zero_timeval() {
        ::timeval result = {};
        return result;
    }
    
    ::timeval value_;
};
   
}}

#endif	/* RS_LIBHTTPSERVER_SOCKET_TIMEVAL_OPTION_H */

