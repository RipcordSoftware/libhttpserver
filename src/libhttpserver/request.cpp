#include "request.h"

rs::httpserver::NullStream rs::httpserver::Request::nullStream_;

bool rs::httpserver::Request::ShouldClose() {
    auto connection = getConnection();
    if (boost::iequals(connection, "close")) {
        return true;
    } else if (IsHttp10() && connection.length() == 0) {
        return true;
    } else {
        return false;
    }
}

rs::httpserver::Stream& rs::httpserver::Request::getRequestStream() {
    if (request_headers_->IsChunked()) {
        return chunkedRequestStream_;
    } else if (request_headers_->getContentLength() > 0) {
        requestStream_.setLength(request_headers_->getContentLength());
        return requestStream_;
    } else {
        return nullStream_;
    }
}

bool rs::httpserver::Request::HasBody() {
    auto method = request_headers_->getMethod();
    return request_headers_->getContentType().length() > 0 &&
        (method == Headers::Put || method == Headers::Post) &&             
        (request_headers_->IsChunked() || request_headers_->getContentLength() > 0);
}