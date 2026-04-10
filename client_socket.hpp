#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP
#include "socket.hpp"
#include <string>

class ClientSocket : public Socket {
    std::string _ip;
public:
    ClientSocket(std::string ip, int port);
    void connect();
    void send(Message message);
    Message receive();
};

#endif
