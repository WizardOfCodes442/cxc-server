
#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <unordered_map>

namespace cxc {
    class HttpRequest {
        public:
            std::string method;
            std::string path;
            std::string http_version;
            std::unordered_map<std::string, std::string> headers;
            std::string body;

            HttpRequest(const std::string& raw_request);
        private:
            void parse_request(const std::string& raw_request);
    };
}
#endif  //HTTP_REQUEST_HPP