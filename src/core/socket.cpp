#include "socket.hpp"
#include <iostream>

namespace cxc {
    Socket::Socket(int domain, int type, int protocol) {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("Failed to initialize Winsock");
        }

        fd = socket(domain, type, protocol);
        if (fd== INVALID_SOCKET) {
            throw std::runtime_error("Failed to create socket");
        }
    }

    void Socket::bind(const sockaddr_in &address) {
        if (::bind(fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
            throw std::runtime_error("Bind failed");
        }
    }

    void Socket::listen(int backlog) {
        if (::listen(fd, backlog) == SOCKET_ERROR) {
            throw std::runtime_error("Listen Failed");
        }
    }

    SOCKET Socket::accept() {
        SOCKET client_fd = ::accept(fd, nullptr, nullptr);
        if (client_fd == INVALID_SOCKET) {
            throw std::runtime_error("Accept Failed");
        }
        return client_fd;
    }

    void Socket::make_non_blocking() {
        u_long mode = 1;
        if(ioctlsocket(fd, FIONBIO, &mode) != 0) {
            throw std::runtime_error("Failed to set non-blocking mode");
        }
    }
    Socket::~Socket() {
        closesocket(fd);
        WSACleanup();
    }
}