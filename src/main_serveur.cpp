#include "serveur.hpp"

int main() {
    Serveur serveur(8080);
    serveur.run();
    return 0;
}
