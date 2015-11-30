#include "headers.h"

const std::string rs::httpserver::Headers::Http10 = "HTTP/1.0";
const std::string rs::httpserver::Headers::Http11 = "HTTP/1.1";

const int rs::httpserver::Headers::DefaultStatusCode = 200;
const std::string rs::httpserver::Headers::DefaultStatusDescription = "";
const std::string rs::httpserver::Headers::DefaultVersion = rs::httpserver::Headers::Http11;

const std::string rs::httpserver::Headers::Get = "GET";
const std::string rs::httpserver::Headers::Post = "POST";
const std::string rs::httpserver::Headers::Put = "PUT";
const std::string rs::httpserver::Headers::Head = "HEAD";
const std::string rs::httpserver::Headers::Delete = "DELETE";

const std::string rs::httpserver::Headers::ContentLength = "Content-Length";
const std::string rs::httpserver::Headers::ContentType = "Content-Type";
const std::string rs::httpserver::Headers::Accept = "Accept";
const std::string rs::httpserver::Headers::AcceptEncoding = "Accept-Encoding";
const std::string rs::httpserver::Headers::ContentEncoding = "Content-Encoding";
const std::string rs::httpserver::Headers::ContentDisposition = "Content-Disposition";
const std::string rs::httpserver::Headers::TransferEncoding = "Transfer-Encoding";
const std::string rs::httpserver::Headers::Expect = "Expect";
const std::string rs::httpserver::Headers::UserAgent = "User-Agent";
const std::string rs::httpserver::Headers::Host = "Host";
const std::string rs::httpserver::Headers::Connection = "Connection";
const std::string rs::httpserver::Headers::KeepAlive = "Keep-Alive";
const std::string rs::httpserver::Headers::Location = "Location";
const std::string rs::httpserver::Headers::LastModified = "Last-Modified";
const std::string rs::httpserver::Headers::ETag = "ETag";
const std::string rs::httpserver::Headers::IfNoneMatch = "If-None-Match";
const std::string rs::httpserver::Headers::IfModifiedSince = "If-Modified-Since";
const std::string rs::httpserver::Headers::CacheControl = "Cache-Control";
const std::string rs::httpserver::Headers::Pragma = "Pragma";
const std::string rs::httpserver::Headers::Range = "Range";
const std::string rs::httpserver::Headers::ContentRange = "Content-Range";