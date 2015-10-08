#include "query_string.h"

#include <algorithm>

void rs::httpserver::QueryString::Parse() const {
    if (lookup_.size() == 0 && data_.size() > 0) {
        auto start = data_.cbegin();
        auto end = data_.cend();
        for (auto pairStart = start, pairEnd = std::find(pairStart, end, '&'); pairStart < end; pairEnd = std::find(pairStart, end, '&')) {
            auto keyEnd = std::find(pairStart, pairEnd, '=');
            if (keyEnd != pairEnd) {
                std::string key{pairStart, keyEnd};
                std::string value{keyEnd + 1, pairEnd};
                lookup_.emplace(std::move(key), std::move(value));
            } else {
                std::string key{pairStart, pairEnd};
                lookup_.emplace(std::move(key), emptyValue_);
            }
            
            pairStart = *pairEnd ? (pairEnd + 1) : pairEnd;
        }            
    }
}

bool rs::httpserver::QueryString::IsKey(const std::string& key) const {
    Parse();
    
    auto pair = lookup_.find(key);
    return pair != lookup_.cend();
}

const std::string& rs::httpserver::QueryString::getValue(const std::string& key) const {
    Parse();
    
    auto pair = lookup_.find(key);
    return pair != lookup_.cend() ? pair->second : emptyValue_;
}

std::vector<std::string> rs::httpserver::QueryString::getKeys() const {
    Parse();
    
    std::vector<std::string> keys;
    for (auto i : lookup_) {
        keys.emplace_back(i.first);
    }
    
    return keys;
}