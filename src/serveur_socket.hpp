#ifndef SERVEUR_SOCKET_HPP
#define SERVEUR_SOCKET_HPP
#include "socket.hpp"

class ServeurSocket : public Socket {
    int _client_fd;
public:
    explicit ServeurSocket(int port);
    void bind();
    void listen();
    void accept();
    void send(Message message);
    Message receive();
    void close_client();
};

#endif
