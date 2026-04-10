#include "serveur.hpp"
#include <iostream>

Serveur::Serveur(int port) : _ss(port) {}

void Serveur::run() {
    _ss.bind();
    _ss.listen();
    std::cerr << "Server ready\n";
    _ss.accept();
    Message msg = _ss.receive();
    std::cout << "Got '" << msg.to_string() << "'\n";
    _ss.close_client();
    _ss.close();
}
