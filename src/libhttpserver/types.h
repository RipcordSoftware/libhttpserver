#ifndef RS_LIBHTTPSERVER_TYPES_H
#define	RS_LIBHTTPSERVER_TYPES_H

#include <boost/shared_ptr.hpp>

namespace rs {
namespace httpwebserver {

class Service;
typedef boost::shared_ptr<Service> service_ptr;

class Socket;
typedef boost::shared_ptr<Socket> socket_ptr;

}}

#endif	/* RS_LIBHTTPSERVER_TYPES_H */

