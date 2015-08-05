#include "request_headers.h"

#include <cctype>

const char rs::httpserver::RequestHeaders::endOfLine_[4] = { '\r', '\n', '\r', '\n' };

const std::string rs::httpserver::RequestHeaders::emptyValue_;

rs::httpserver::request_headers_ptr rs::httpserver::RequestHeaders::Create(HeaderBuffer& buffer) {
    auto headersEnd = std::search(buffer.cbegin(), buffer.cend(), endOfLine_, endOfLine_ + sizeof(endOfLine_));
    
    if (headersEnd != buffer.cend()) {
        auto headers = request_headers_ptr(new RequestHeaders());
        auto headersLength = headersEnd - buffer.cbegin() + sizeof(endOfLine_);
        headers->GetHeaders(buffer, headersLength);
        buffer.setPosition(headersLength);
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
    
    method_.assign(methodStart, methodEnd);
    
    while (*++methodEnd == ' ');

    auto uriStart = methodEnd;
    auto uriEnd = std::find(uriStart, headersEnd, ' ');
    if (methodEnd == headersEnd) {
        throw HeaderMalformedException();
    }
    
    rawUri_.assign(uriStart, uriEnd);
    
    while (*++uriEnd == ' ');
    
    auto versionStart = uriEnd;
    auto versionEnd = std::find(versionStart, headersEnd, '\r');
    if (versionEnd == headersEnd || versionEnd == versionStart) {
        throw HeaderMalformedException();
    }
    
    auto lineStart = versionEnd + 2;
            
    while (*(versionEnd - 1) == ' ') { --versionEnd; }
    version_.assign(versionStart, versionEnd);
        
    if (version_.find("HTTP/") != 0 || version_.length() != 8 || !std::isdigit(version_[5]) || version_[6] != '.' || !std::isdigit(version_[7])) {
        throw HeaderMalformedException();
    }        
           
    while (lineStart < headersEnd && *lineStart != '\r') {
        auto nameStart = lineStart;
        auto nameEnd = std::find(nameStart, headersEnd, ':');
        if (nameEnd == headersEnd) {
            throw HeaderMalformedException();
        }

        auto valueStart = nameEnd + 1;        
        while (*valueStart == ' ') {
            ++valueStart;
        }
        
        auto valueEnd = std::find(valueStart, headersEnd, '\r');
        if (valueEnd == headersEnd) {
            throw HeaderMalformedException();
        }
        
        lineStart = valueEnd + 2;

        while (*(nameEnd - 1) == ' ') {
            --nameEnd;
        }                
        
        while (*(valueEnd - 1) == ' ') {
            --valueEnd;
        }

        std::string name(nameStart, nameEnd);
        std::string value(valueStart, valueEnd);
        
        headers_.emplace(std::move(name), std::move(value));                
    }
    
    auto queryStringStart = std::find(rawUri_.cbegin(), rawUri_.cend(), '?');
    if (queryStringStart != rawUri_.cend()) {
        uri_ = std::string(rawUri_.cbegin(), queryStringStart);
        queryString_ = UriDecode(std::string(queryStringStart + 1, rawUri_.cend()));
    } else {
        uri_ = rawUri_;
        queryString_ = emptyValue_;
    }
}

std::string rs::httpserver::RequestHeaders::UriDecode(const std::string& data) {            
    if (data.find('%') != std::string::npos) {
        auto size = data.size();
        std::string decodedData;
        decodedData.reserve(size);
        
        for (decltype(size) i = 0; i < size; ++i) {
            auto ch = data[i];
            if (ch == '%' && (i + 2) < size && std::isxdigit(data[i + 1]) && std::isxdigit(data[i + 2])) {
                unsigned code = GetDigitValue(data[++i]) << 4;
                code |= GetDigitValue(data[++i]);
                decodedData.push_back((char)code);
            } else {
                decodedData.push_back(ch);
            }                        
        }
        
        return decodedData;
    } else {
        return data;
    }        
}

unsigned rs::httpserver::RequestHeaders::GetDigitValue(char ch) {
    if (ch >= 0x30 && ch <= 0x39) {
        return ch - 0x30;
    } else {
        return (ch | 0x20) - 0x61 + 10;
    }
}