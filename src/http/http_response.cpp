#include "http_response.hpp"
#include <sstream>

namespace cxc {
    // Constructor for HttpResponse
    HttpResponse::HttpResponse(int status_code, const std::string& body)
        : http_version("HTTP/1.1"), status_code(status_code), body(body) {
        // Set default status messages
        if (status_code == 200) status_message = "OK";
        else if (status_code == 404) status_message = "Not Found";
        else status_message = "Unknown Status";

        // Add default headers
        headers["Content-Length"] = std::to_string(body.size());
        headers["Content-Type"] = "text/plain";
    }

    // Convert response to raw HTTP response string
    std::string HttpResponse::to_string() const {
        std::ostringstream response_stream;

        // Status line
        response_stream << http_version << " " << status_code << " " << status_message << "\r\n";

        // Headers
        for (auto it = headers.begin(); it != headers.end(); ++it) {
            response_stream << it->first << ": " << it->second << "\r\n";
        }

        // Blank line between headers and body
        response_stream << "\r\n";

        // Body
        response_stream << body;

        return response_stream.str();
    }
}
