#ifndef SERVEUR_HPP
#define SERVEUR_HPP
#include "serveur_socket.hpp"
#include "message.hpp"

class Serveur {
    ServeurSocket _ss;
    unsigned int _width;
    unsigned int _height;
public:
    explicit Serveur(int port, unsigned int width = 800, unsigned int height = 600);
    Request listen_req();
    void run();
    void send_response(const Message& msg);
    void close_current_client();
};

#endif
