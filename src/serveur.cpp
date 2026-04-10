#include "serveur.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Serveur::Serveur(int port) : _ss(port) { std::srand(std::time(nullptr)); }

void Serveur::run() {
    _ss.bind();
    _ss.listen();
    std::cerr << "Server ready\n";
    while (true) {
        _ss.accept();
        while (true) {
            Message msg = _ss.receive();
            if (msg.get_type() == INFO) break;
            std::string content = msg.to_string();
            std::cout << "received: " << content << "\n";
            if (content.rfind("roll ", 0) == 0) {
                int n = std::stoi(content.substr(5));
                int result = std::rand() % (n + 1);
                std::string response = std::to_string(result);
                std::cout << "sent: " << response << "\n";
                _ss.send(Message(response, TEXT));
            } else {
                std::cerr << "unknown command: " << content << "\n";
                _ss.send(Message("error: unknown command", TEXT));
            }
        }
        _ss.close_client();
    }
}
