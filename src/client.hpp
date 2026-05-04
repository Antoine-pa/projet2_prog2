#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "client_socket.hpp"

class Client {
    ClientSocket _cs;
public:
    Client(std::string ip, int port);
    void send(const Message& msg);
    void run();
    void connect();
    void close();
    Message receive();
    std::pair<int,int> get_canvas_size();
};

#endif
