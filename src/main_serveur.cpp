#include "serveur.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[]) {
    int port = 8080;

    try {
        Serveur serveur(port);
        std::cout << "Serveur démarré sur le port " << port << ".\n";

        // Boucle principale de traitement des requêtes
        while (true) {
            // listen_req() bloque jusqu'à recevoir une requête valide avec r, g, b
            Request req = serveur.listen_req();
            
            std::cout << "[Serveur] Requête reçue - R: " << req.get_r() 
                      << " | G: " << req.get_g() 
                      << " | B: " << req.get_b() << "\n";

        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur critique : " << e.what() << "\n";
        return 1;
    }

    return 0;
}