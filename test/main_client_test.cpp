#include <iostream>
#include <string>
#include <thread>
#include "../src/client.hpp"
#include "../src/message.hpp"
#include "../src/displayer.hpp"

static int port;
static int passed = 0;
static int failed = 0;

void check(const std::string& name, bool ok) {
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << "\n";
    ok ? passed++ : failed++;
}

std::string send_pixel(int x, int y, int r, int g, int b) {
    Client c("127.0.0.1", port);
    c.connect();
    c.send(Message(std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(r)+" "+std::to_string(g)+" "+std::to_string(b), REQ));
    return c.receive().to_string();
}

std::string send_raw(const std::string& content) {
    Client c("127.0.0.1", port);
    c.connect();
    c.send(Message(content, TEXT));
    return c.receive().to_string();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }
    port = std::stoi(argv[1]);

    // Test 1: recuperation de la taille du canvas
    Client c("127.0.0.1", port);
    auto [w, h] = c.get_canvas_size();
    check("Recuperation taille canvas", w > 0 && h > 0);

    // Test 2: pixel valide
    check("Pixel valide", send_pixel(0, 0, 255, 0, 0) == "OK");

    // Test 3: coins du canvas
    check("Coin haut-gauche (0,0)",       send_pixel(0,   0,   255, 0,   0  ) == "OK");
    check("Coin haut-droit  (w-1,0)",     send_pixel(w-1, 0,   0,   255, 0  ) == "OK");
    check("Coin bas-gauche  (0,h-1)",     send_pixel(0,   h-1, 0,   0,   255) == "OK");
    check("Coin bas-droit   (w-1,h-1)",   send_pixel(w-1, h-1, 255, 255, 0  ) == "OK");

    // Test 4: hors-canvas
    check("Hors-canvas x=w",   send_pixel(w,  0,  0, 0, 0) != "OK");
    check("Hors-canvas y=h",   send_pixel(0,  h,  0, 0, 0) != "OK");
    check("Hors-canvas x=-1",  send_pixel(-1, 0,  0, 0, 0) != "OK");
    check("Serveur stable apres hors-canvas", send_pixel(1, 1, 128, 128, 128) == "OK");

    // Test 5: couleurs invalides
    check("Couleur r > 255",              send_pixel(0, 0, 256,  0,   0  ) != "OK");
    check("Couleur g > 255",              send_pixel(0, 0, 0,    256, 0  ) != "OK");
    check("Couleur b > 255",              send_pixel(0, 0, 0,    0,   256) != "OK");
    check("Couleur negative",             send_pixel(0, 0, -1,   0,   0  ) != "OK");
    check("Serveur stable apres couleur invalide", send_pixel(3, 3, 255, 255, 255) == "OK");

    // Test 6: message malformé
    check("Message malformé rejeté",            send_raw("blabla") != "OK");
    check("Serveur stable apres msg malformé",  send_pixel(2, 2, 64, 64, 64) == "OK");

    // Test 7: displayer
    {
        // Pixel connu avant connexion du displayer
        send_pixel(5, 5, 42, 43, 44);

        Displayer d("127.0.0.1", port + 1);
        auto [dw, dh] = d.get_canvas_size();
        auto pixels = d.receive_initial_canvas();

        bool found = false;
        for (auto [x, y, r, g, b] : pixels)
            if (x == 5 && y == 5 && r == 42 && g == 43 && b == 44) found = true;

        check("Displayer: taille canvas correcte", dw == w && dh == h);
        check("Displayer: canvas initial contient le pixel connu", found);

        // Envoi d'un update dans un thread, reception cote displayer
        std::thread t([&]{ send_pixel(6, 7, 10, 20, 30); });
        auto [ux, uy, ur, ug, ub] = d.receive_update();
        t.join();
        check("Displayer: update recu", ux == 6 && uy == 7 && ur == 10 && ug == 20 && ub == 30);
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " tests passes\n";
    return (failed == 0) ? 0 : 1;
}
