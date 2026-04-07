#ifndef SOCKET_HPP
#define SOCKET_HPP
#include "message.hpp"

class Socket {
    fd;
    int port const;
    addri sockaddr_in; //à définir 
    const int FORMAT
    public:
        explicit Socket(int port)
        void close();
        void send(fd, Message message);
        Message receive();
        
};

#endif