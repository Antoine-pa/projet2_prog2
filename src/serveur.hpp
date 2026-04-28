#ifndef SERVEUR_HPP
#define SERVEUR_HPP
#include "serveur_socket.hpp"
#include "message.hpp"

class Serveur {
    ServeurSocket _ss;
public:
    explicit Serveur(int port);
    Request listen_req();
    void run();
};

#endif
