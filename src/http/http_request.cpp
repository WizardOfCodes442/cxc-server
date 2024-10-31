#include "http_request.hpp"
#include <sstream>
#include <iostream>

namespace cxc {
    // Constructor that parses raw HTTP request
    HttpRequest::HttpRequest(const std::string& raw_request) {
        parse_request(raw_request);
    }

    void HttpRequest::parse_request(const std::string& raw_request) {
        std::istringstream request_stream(raw_request);
        std::string line;

        // Parse request line (e.g., GET /index.html HTTP/1.1)
        if (std::getline(request_stream, line)) {
            std::istringstream request_line(line);
            request_line >> method >> path >> http_version;
        }

        // Parse headers
        while (std::getline(request_stream, line) && line != "\r") {
            size_t delimiter = line.find(": ");
            if (delimiter != std::string::npos) {
                std::string header_name = line.substr(0, delimiter);
                std::string header_value = line.substr(delimiter + 2);
                headers[header_name] = header_value;
            }
        }

        // Parse body if present
        if (request_stream.good()) {
            std::ostringstream body_stream;
            body_stream << request_stream.rdbuf();  // Read until the end of the stream
            body = body_stream.str();
        }
    }
}
