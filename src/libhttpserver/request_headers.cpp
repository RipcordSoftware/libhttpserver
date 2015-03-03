#include "request_headers.h"

const char rs::httpserver::RequestHeaders::endOfLine_[4] = { '\r', '\n', '\r', '\n' };

const std::string rs::httpserver::RequestHeaders::emptyValue_;

rs::httpserver::request_headers_ptr rs::httpserver::RequestHeaders::Create(const HeaderBuffer& buffer) {
    auto headersEnd = std::search(buffer.cbegin(), buffer.cend(), endOfLine_, endOfLine_ + sizeof(endOfLine_));
    
    if (headersEnd != buffer.cend()) {
        auto headers = request_headers_ptr(new RequestHeaders());
        headers->GetHeaders(buffer, headersEnd - buffer.cbegin() + sizeof(endOfLine_));
        return headers;
    } else {
        return nullptr;
    }
}

void rs::httpserver::RequestHeaders::GetHeaders(const HeaderBuffer& buffer, int headersLength) {
    auto headersStart = buffer.cbegin();
    auto headersEnd = headersStart + headersLength;
    
    auto methodStart = headersStart;
    auto methodEnd = std::find(headersStart, headersEnd, ' ');
    if (methodEnd == headersEnd) {
        throw HeaderMalformedException();
    }
    
    auto uriStart = methodEnd + 1;
    auto uriEnd = std::find(uriStart, headersEnd, ' ');
    if (methodEnd == headersEnd) {
        throw HeaderMalformedException();
    }
    
    auto versionStart = uriEnd + 1;
    auto versionEnd = std::find(uriStart, headersEnd, '\r');
    if (versionEnd == headersEnd) {
        throw HeaderMalformedException();
    }    
    
    method_ = std::move(std::string(methodStart, methodEnd));
    rawUri_ = std::move(std::string(uriStart, uriEnd));
    version_ = std::move(std::string(versionStart, versionEnd));
    
    auto lineStart = versionEnd + 2;
    
    while (lineStart < headersEnd && *lineStart != '\r') {
        auto fieldStart = lineStart;
        auto fieldEnd = std::find(fieldStart, headersEnd, ':');
        if (fieldEnd == headersEnd) {
            throw HeaderMalformedException();
        }

        auto valueStart = fieldEnd + 1;        
        while (*valueStart == ' ') {
            ++valueStart;
        }
        
        auto valueEnd = std::find(valueStart, headersEnd, '\r');
        if (valueEnd == headersEnd) {
            throw HeaderMalformedException();
        }       

        while (*(fieldEnd - 1) == ' ') {
            --fieldEnd;
        }
        
        while (*(valueEnd - 1) == ' ') {
            --valueEnd;
        }

        std::string field(fieldStart, fieldEnd);
        std::string value(valueStart, valueEnd);
        
        headers_[std::move(field)] = std::move(value);
        
        lineStart = valueEnd + 2;
    }
    
    auto queryStringStart = std::find(rawUri_.cbegin(), rawUri_.cend(), '?');
    if (queryStringStart != rawUri_.cend()) {
        uri_ = std::move(std::string(rawUri_.cbegin(), queryStringStart));
        queryString_ = std::move(std::string(queryStringStart + 1, rawUri_.cend()));
    } else {
        uri_ = rawUri_;
        queryString_ = emptyValue_;
    }
}