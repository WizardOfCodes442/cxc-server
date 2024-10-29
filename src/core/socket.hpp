#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")   //Link with Winsock library 

namespace cxc {
    class Socket {
    public:
        SOCKET fd;
        Socket(int domain, int type, int protocol);
        void bind(const sockaddr_in& address);
        void listen(int backlog = 10);
        SOCKET accept();
        void make_non_blocking();
        ~Socket();
    };
};

#endif
