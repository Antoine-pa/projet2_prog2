#ifndef SERVEUR_HPP
#define SERVEUR_HPP
#include "serveur_socket.hpp"

class Serveur {
    ServeurSocket _ss;
public:
    explicit Serveur(int port);
    void run();
};

#endif
