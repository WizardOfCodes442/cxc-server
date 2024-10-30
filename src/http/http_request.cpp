#include "http_request.hpp"
#include <sstream>
#include <iostream>

 namespace cxc {
    //constructor that parses raw HTTP reequest
    HttpRequest::HttpRequest(const std::string& raw_request) {
        parse_request(raw_request);
    }

    void HttpRequest::parse_request(const std::string& raw_request) {
        std::istringstream request_stream(raw_request);
        std::string line;

        //Parse request line(e.g GET/index.html HTTP/1.1)
        std::getline(request_stream, line);
        std::istringstream request_line(line);
        request_line >> method >> path >> http_version;

        //Parse headers
        while (std::getline(request_stream, line) && line != "\r") {
            size_t delimeter = line.find(": ");
            if (delimeter != std::string::npos) {
                std::string header_name = line.substr(0, delimeter);
                std::string header_value = line.substr(delimeter + 2);
                headers[header_name] = header_value; 
            }
        }
        //Parse body (if present)
        std::getline(request_stream, body);
    }
 }