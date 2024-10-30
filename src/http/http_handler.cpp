#include "http_handler.hpp"

namespace cxc {

    // Handle incoming HTTP request and generate response
    HttpResponse HttpHandler::handle_request(const HttpRequest& request) {
        if (request.path == "/") {
            return HttpResponse(200, "Welcome to CXC Server!");
        } else {
            return HttpResponse(404, "Page not found");
        }
    }
}
