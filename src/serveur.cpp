#include "serveur.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <ctime>

Serveur::Serveur(int port) : _ss(port) { std::srand(std::time(nullptr)); }

Request Serveur::listen_req() {
    _ss.bind();
    _ss.listen();
    std::cerr << "Server ready\n";
    
    while (true) {
        _ss.accept();
        
        while (true) {
            Message msg = _ss.receive();
            
            if (msg.get_type() == REQ) {
                std::string content = msg.to_string();
                std::cout << "received: " << content << "\n";
                
                int r = 0, g = 0, b = 0, x = 0, y = 0;
                std::istringstream iss(content);
                
                if (iss >> r >> g >> b) {
                    return Request(r, g, b, x, y);
                } else {
                    std::cerr << "error: invalid coordinate format\n";
                    _ss.send(Message("error: invalid format", ERROR));
                }
            } else {
                std::cerr << "unknown command: " << msg.to_string() << "\n";
                _ss.send(Message("error: expected REQ", ERROR));
                break; // On casse la boucle pour fermer ce client et en attendre un autre
            }
        }
        _ss.close_client();
    }
}

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
