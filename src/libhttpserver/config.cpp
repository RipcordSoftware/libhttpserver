#include "config.h"

const unsigned rs::httpserver::Config::MinThreadCount = 20;
const unsigned rs::httpserver::Config::MaxThreadCount = 200;
const unsigned rs::httpserver::Config::ThreadCoreMultiplier = 16;

const int rs::httpserver::Config::MaxRequestCount = 100;

const int rs::httpserver::Config::HeaderReceiveTimeoutPeriod = 30;
const int rs::httpserver::Config::BodyReceiveTimeoutPeriod = 60;    
const int rs::httpserver::Config::KeepAliveTimeout = 10;
const int rs::httpserver::Config::KeepAliveTimeoutGrace = 2;
const int rs::httpserver::Config::KeepAliveTimeoutTotal = KeepAliveTimeout + KeepAliveTimeoutGrace;

const int rs::httpserver::Config::MaxRequestHeaderSize = 16384;
const int rs::httpserver::Config::MaxResponseChunkSize = 2048;