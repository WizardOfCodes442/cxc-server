#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <unordered_map>

namespace cxc {
    class HttpResponse {
        public: 
            std::string http_version;
            int status_code;
            std::string status_message;
            std::unordered_map<std::string, std::string> headers;
            std::string body;

            HttpResponse(int status_code, const std::string& body);
            std::string to_string() const;
    };
}

#endif  //HTTP_RESPONSE_HPP
