#include "request_router.h"

#include "request.h"
#include "response.h"

rs::httpserver::RequestRouter::RequestRouter() : 
    routes_({ {"GET",{}}, {"PUT",{}}, {"POST",{}}, {"DELETE",{}}, {"HEAD",{}} }) {
}

void rs::httpserver::RequestRouter::Add(const char* method, const char* re, Callback func) {
    std::vector<std::string> namedGroups;

    const char* namedGroupStart = re;
    while ((namedGroupStart = std::strstr(namedGroupStart, "(?<")) != nullptr) {
        namedGroupStart += 3;
        auto namedGroupPtr = namedGroupStart;
        while (*namedGroupPtr != '>' && *namedGroupPtr) {
            ++namedGroupPtr;
        }            

        namedGroups.emplace_back(namedGroupStart, namedGroupPtr);
        namedGroupStart = namedGroupPtr + 1;
    }       
    
    if (routes_.find(method) == routes_.cend()) {
        routes_[method] = {};
    }

    routes_[method].push_back(std::make_tuple(boost::basic_regex<char>(re), func, namedGroups));
}

bool rs::httpserver::RequestRouter::Match(request_ptr request, response_ptr response) const {
    auto method = request->getMethod();
    auto methodRoutes = routes_.find(method);
    
    if (methodRoutes != routes_.cend()) {
        for (auto route : methodRoutes->second) {
            boost::match_results<const char*> what;
            if (boost::regex_match(request->getUri().c_str(), what, std::get<0>(route))) {
                CallbackArgs groups;
                std::vector<std::string> heapValues;
                for (auto& name : std::get<2>(route)) {                    
                    auto value = what[name];
                    auto valueLength = value.second - value.first;                    
                    if (valueLength < 128) {
                        auto valueBuffer = reinterpret_cast<char*>(alloca(valueLength + 1));
                        std::strncpy(valueBuffer, value.first, valueLength);
                        valueBuffer[valueLength] = '\0';
                        groups.emplace(name.c_str(), valueBuffer);
                    } else {
                        heapValues.emplace_back(value.str());
                        groups.emplace(name.c_str(), heapValues.back().c_str());
                    }
                }
                if ((std::get<1>(route))(request, groups, response)) {
                    return true;
                }
            }
        }
    }
    
    return false;
}   