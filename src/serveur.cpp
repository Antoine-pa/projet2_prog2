#include "serveur.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <ctime>

void Serveur::send_response(const Message& msg) {
    _ss.send(msg);
}

void Serveur::close_current_client() {
    _ss.close_client();
}

Serveur::Serveur(int port, unsigned int width, unsigned int height)
    : _ss(port), _width(width), _height(height) {
    std::srand(std::time(nullptr));
    _ss.bind();
    _ss.listen();
    std::cerr << "[Serveur] Demarre sur le port " << port << " (" << width << "x" << height << ")\n";
}

Request Serveur::listen_req() {
    while (true) {
        _ss.accept();
        Message msg = _ss.receive();
        std::string content = msg.to_string();

        if (content == "size") {
            std::string response = std::to_string(_width) + " " + std::to_string(_height);
            _ss.send(Message(response, INFO));
            _ss.close_client();
            continue;
        }

        int x = 0, y = 0, r = 0, g = 0, b = 0;
        std::istringstream iss(content);
        if (iss >> x >> y >> r >> g >> b) {
            if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
                std::cerr << "[Erreur] Couleur invalide: " << content << "\n";
                _ss.send(Message("error: invalid color", ERROR));
                _ss.close_client();
                continue;
            }
            if (x < 0 || (unsigned int)x >= _width || y < 0 || (unsigned int)y >= _height) {
                std::cerr << "[Erreur] Coordonnees hors-canvas: " << content << "\n";
                _ss.send(Message("error: out of bounds", ERROR));
                _ss.close_client();
                continue;
            }
            return Request(x, y, r, g, b);
        } else {
            std::cerr << "[Erreur] Format invalide recu: " << content << "\n";
            _ss.send(Message("error: invalid format", ERROR));
            _ss.close_client();
        }
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
