#ifndef HTTP_HANDLER_HP
#define HTTP_HANDLER_HPP

#include "http_request.hpp"
#include "http_response.hpp"

namespace cxc {
    class HttpHandler {
        public:
            HttpResponse handle_request(const HttpRequest& request);
    };
}

#endif //HTTP_HANDLER_HPP