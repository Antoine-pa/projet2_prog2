#ifndef SOCKET_HPP
#define SOCKET_HPP
#include "message.hpp"
#include <netinet/in.h>

class Socket {
protected:
    int _fd;
    int _port;
    struct sockaddr_in _addr;
    void send(int fd, Message message);
    Message receive(int fd);
public:
    explicit Socket(int port);
    void close();
    int get_fd() const { return _fd; }
};

#endif
