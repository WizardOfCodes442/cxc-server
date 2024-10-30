#ifdef _WIN32
    #define CLOSE_SOCKET closesocket
#else   
    #define CLOSE_SOCKET close
#endif

#include "core/socket.hpp"
#include "core/event_loop.hpp"
#include "http/http_handler.hpp"
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "modules/module_manager.hpp"
#include "modules/logger_module.hpp"
#include <iostream>
#include <vector>

int main() {
    //Initialize Winsock (only needed on Windows)
#ifndef _WIN32 
    WSDATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }
#endif

    //Initialize the server socket 
    cxc::Socket server_socket(AF_INET, SOCK_STREAM, 0);

    //Bind and Listen on Port 8080
    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    server_socket.bind(server_addr);
    server_socket.listen();

    std::cout << "Server listening onm port 8080.." << std::endl;

    //Initialize Module manager and register modules 
    cxc::ModuleManager module_manager;
    module_manager.register_module(std::make_unique<cxc::LoggerModule>());
    module_manager.init_modules();

    //Accept a client connection
    int client_fd = server_socket.accept();

    //Read request from the client 
    char buffer[1024] = {0};
#ifdef _WIN32
    int bytes_recieved = recv (client_fd, buffer, 1024, 0);
    if (bytes_recieved < 0 ) {
        std::cerr << "recv() failed. \n";
        return 1;
    }
#else
    int bytes_recieved = read(client_fd, buffer, 1024);
    if (bytes_recieved < 0) {
        std::cerr << "read()  failed.\n";
        return 1;
    }
#endif
    //Handle HTTP request
    cxc::HttpRequest request(buffer);
    cxc::HttpHandler handler;
    cxc::HttpResponse response = handler.handle_request(request);

    //pass the request to the module manager for logging 
    std::string module_response = module_manager.handle_request(buffer);

    //Include module response in HTTP response body
    response.body += "\n" + module_response;

    //Send HTTP response to client
    std::string response_str = response.to_string();
    send(client_fd, response_str.c_str(), response_str.size(), 0);

    //close client socket
    CLOSE_SOCKET(client_fd);

    //shutdown all modules 
    module_manager.shutdown_modules();
#ifdef _WIN32
    WSACleanup();

#endif
    return 0; 
}