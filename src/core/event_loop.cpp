#include "event_loop.hpp"
#include <iostream>

namespace cxc {
    //Constructor: Create the IO Completion Port 
    EventLoop::EventLoop() {
        iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        if (iocp ==NULL) {
            throw std::runtime_error("Failed to create IO Completion Port");
        }
    }

    //Associate a socket with IOCP
    void EventLoop::add_socket(SOCKET socket) {
        if (CreateIoCompletionPort((HANDLE)socket, iocp, 0, 0)  == NULL) {
            throw std::runtime_error("Failed to associate socket with IOCP");
        }
    }

    //Start the event Loop (blocking call)
    void EventLoop::run() {
        DWORD bytesTransferred;
        ULONG_PTR completionKey;
        LPOVERLAPPED overlapped;

        std::cout << "Event loop started..." << std::endl;

        while(true) {
            BOOL result = GetQueuedCompletionStatus(
                iocp,  //IOCP handle
                &bytesTransferred, //Number of bytes transferred
                &completionKey, //Completion key (can be a socket or other identifier)
                &overlapped, //Overlapped structure contains io context
                INFINITE   //wait indefinitely
            );

            if (!result) {
                std::cerr << "IOCP wait failed: " << GetLastError() << std::endl;
                continue;
            }

            std::cout << "I/O Operation completed on socket" << std::endl;
            //TODO: call a callback or handler here based on completionKey
        }
    }

    //Destructor: Close the IOCP handle
    EventLoop::~EventLoop() {
        CloseHandle(iocp);
    }
}