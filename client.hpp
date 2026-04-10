#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "client_socket.hpp"

class Client {
    ClientSocket _cs;
public:
    Client(std::string ip, int port);
    void run();
};

#endif
