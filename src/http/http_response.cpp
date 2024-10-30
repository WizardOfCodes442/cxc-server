#include "http_response.hpp"
#include <sstream>

namespace cxc {
    //constructor for Httpreesponse 
    HttpResponse::HttpResponse(int status_code, const std::string& body) : http_version("HTTP/1.1"), status_code(status_code), body(body) {
        // set default status messages 
        if (status_code == 200) status_message = "OK";
        else if (status_code == 404) status_message = "Not Found";
        else status_message = "unknoiwn status";

        //Add default headers 
        headers["content-Length"] = std::to_string(body.size());
        headers["content-Type"] = "text/plain";
    }

    //convert response to raw HTTP resposne string 
    std::string HttpResponse::to_string() const {
        std::ostringstream response_stream;

        //status line 
        response_stream << http_version << " " << status_code << " " << status_message <<"\r\n";

        //Headers
        for (const auto& [key, value] : headers) {
            response_stream << key << ": " << value << "\r\n";
        }

        //Blank Line between headers and body
        response_stream << "\r\n";

        //Body
        response_stream << body;

        return response_stream.str();
    }
}