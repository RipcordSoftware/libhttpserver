#include "request_headers.h"

const char rs::httpserver::RequestHeaders::endOfLine_[4] = { '\r', '\n', '\r', '\n' };

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
    
    auto urlStart = methodEnd + 1;
    auto urlEnd = std::find(urlStart, headersEnd, ' ');
    if (methodEnd == headersEnd) {
        throw HeaderMalformedException();
    }
    
    auto versionStart = urlEnd + 1;
    auto versionEnd = std::find(urlStart, headersEnd, '\r');
    if (versionEnd == headersEnd) {
        throw HeaderMalformedException();
    }    
    
    method_ = std::move(std::string(methodStart, methodEnd));
    uri_ = std::move(std::string(urlStart, urlEnd));
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
}