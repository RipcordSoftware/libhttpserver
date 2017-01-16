#include "request_headers.h"

#include <limits>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <cctype>

const char rs::httpserver::RequestHeaders::endOfLine_[4] = { '\r', '\n', '\r', '\n' };

const std::string rs::httpserver::RequestHeaders::emptyValue_;

const rs::httpserver::RequestHeaders::range_index rs::httpserver::RequestHeaders::RANGE_END = 
    std::numeric_limits<rs::httpserver::RequestHeaders::range_index>::max();

rs::httpserver::request_headers_ptr rs::httpserver::RequestHeaders::Create(HeaderBuffer& buffer) {
    auto headersEnd = std::search(buffer.cbegin(), buffer.cend(), endOfLine_, endOfLine_ + sizeof(endOfLine_));
    
    if (headersEnd != buffer.cend()) {
        auto headers = boost::make_shared<RequestHeaders>();
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
        throw HeaderMalformedException("Missing method");
    }
    
    method_.assign(methodStart, methodEnd);
    
    while (*++methodEnd == ' ');

    auto uriStart = methodEnd;
    auto uriEnd = std::find(uriStart, headersEnd, ' ');
    if (methodEnd == headersEnd) {
        throw HeaderMalformedException("Missing URI");
    }
    
    rawUri_.assign(uriStart, uriEnd);
    
    while (*++uriEnd == ' ');
    
    auto versionStart = uriEnd;
    auto versionEnd = std::find(versionStart, headersEnd, '\r');
    if (versionEnd == headersEnd || versionEnd == versionStart) {
        throw HeaderMalformedException("Missing version");
    }
    
    auto lineStart = versionEnd + 2;
            
    while (*(versionEnd - 1) == ' ') { --versionEnd; }
    version_.assign(versionStart, versionEnd);
        
    if (version_.find("HTTP/") != 0 || version_.length() != 8 || !std::isdigit(version_[5]) || version_[6] != '.' || !std::isdigit(version_[7])) {
        throw HeaderMalformedException("Malformed version");
    }        
           
    while (lineStart < headersEnd && *lineStart != '\r') {
        auto nameStart = lineStart;
        auto nameEnd = std::find(nameStart, headersEnd, ':');
        if (nameEnd == headersEnd) {
            throw HeaderMalformedException("Bad header key");
        }

        auto valueStart = nameEnd + 1;        
        while (*valueStart == ' ') {
            ++valueStart;
        }
        
        auto valueEnd = std::find(valueStart, headersEnd, '\r');
        if (valueEnd == headersEnd) {
            throw HeaderMalformedException("Bad header value");
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

rs::httpserver::RequestHeaders::byte_range_collection rs::httpserver::RequestHeaders::getByteRanges() {
    byte_range_collection ranges;
    
    auto range = getRange();    
    if (range.size() > 0 && boost::algorithm::istarts_with(range, "bytes=")) {
        range = std::string{range.cbegin() + 6, range.cend()};

        std::vector<std::string> splitRanges;
        boost::split(splitRanges, range, boost::is_any_of(","), boost::token_compress_off);

        try {
            for (auto splitRange : splitRanges) {                
                auto splitIndex = splitRange.find('-');
                if (splitIndex == 0 || splitIndex == std::string::npos) {
                    auto start = boost::lexical_cast<range_index>(splitRange);
                    ranges.emplace_back(start, RANGE_END);
                } else {
                    auto str = splitRange.c_str();
                    auto start = boost::lexical_cast<byte_range_collection::value_type::first_type>(str, splitIndex);
                    auto end = splitIndex < (splitRange.size() - 1) ? boost::lexical_cast<range_index>(str + splitIndex + 1) : RANGE_END;
                    ranges.emplace_back(start, end);
                }
            }
        } catch (const boost::bad_lexical_cast&) {
            ranges.clear();
        }
    }
    
    return ranges;
}