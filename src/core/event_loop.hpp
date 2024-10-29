#ifndef EVENT_LOOP_HPP
#define EVENT_LOOP_HPP

#include <winsock2.h>   //For socket functions
#include <windows.h>
#include <stdexcept>

namespace cxc { 
    class EventLoop {
        private: 
            HANDLE iocp; //IO competion handle 

        public: 
            EventLoop();  //Constructor 
            void add_socket(SOCKET socket);  //Associate a socket with IOCP
            void run();   //Start the event Loop
            ~EventLoop();  //Destructor

    };
}

#endif