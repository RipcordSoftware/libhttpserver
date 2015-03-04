#include "config.h"

const int rs::httpserver::Config::MaxResponseCount = 100;

const int rs::httpserver::Config::HeaderReceiveTimeoutPeriod = 30;
const int rs::httpserver::Config::BodyReceiveTimeoutPeriod = 60;    
const int rs::httpserver::Config::KeepAliveTimeout = 10;
const int rs::httpserver::Config::KeepAliveTimeoutGrace = 2;
const int rs::httpserver::Config::KeepAliveTimeoutTotal = KeepAliveTimeout + KeepAliveTimeoutGrace;

const int rs::httpserver::Config::MaxRequestHeaderSize = 16384;