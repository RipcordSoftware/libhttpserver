#include "query_string.h"

#include <algorithm>

void rs::httpserver::QueryString::Parse() const {
    if (lookup_.size() == 0 && data_.size() > 0) {
        auto start = data_.cbegin();
        auto end = data_.cend();
        for (auto pairStart = start, pairEnd = std::find(pairStart, end, '&'); pairStart < end; pairEnd = std::find(pairStart, end, '&')) {
            auto keyEnd = std::find(pairStart, pairEnd, '=');
            if (keyEnd != pairEnd) {
                auto key = std::move(std::string(pairStart, keyEnd));
                auto value = std::move(std::string(keyEnd + 1, pairEnd));
                lookup_[std::move(key)] = std::move(value);
            } else {
                auto key = std::move(std::string(pairStart, pairEnd));
                lookup_[std::move(key)] = emptyValue_;
            }
            
            pairStart = pairEnd + 1;
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
        keys.push_back(i.first);
    }
    
    return keys;
}