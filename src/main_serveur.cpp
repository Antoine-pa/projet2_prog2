#include "serveur.hpp"
#include "image_editor.hpp"
#include "displayer_manager.hpp"
#include <thread>
#include <iostream>
#include <functional>
#include <string>

void reception_reseau(Serveur& serveur, ImageEditor& editor, DisplayerManager& disp) {
    while (true) {
        try {
            Request req = serveur.listen_req();

            editor.update_pixel_from_request(req.get_x(), req.get_y(), req.get_r(), req.get_g(), req.get_b());
            serveur.send_response(Message("OK", INFO));
            serveur.close_current_client();
            disp.broadcast(req.get_x(), req.get_y(), req.get_r(), req.get_g(), req.get_b());

        } catch (const std::exception& e) {
            std::cerr << "[CRASH RESEAU] " << e.what() << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port> [width height]\n";
        return 1;
    }
    int port = std::stoi(argv[1]);
    unsigned int width  = (argc >= 4) ? std::stoul(argv[2]) : 800;
    unsigned int height = (argc >= 4) ? std::stoul(argv[3]) : 600;

    Serveur serveur(port, width, height);
    ImageEditor editor(width, height);
    DisplayerManager disp(port + 1);

    std::cout << "Serveur lance sur le port " << port << " (displayers: " << port + 1 << ")...\n";

    std::thread net_thread(reception_reseau, std::ref(serveur), std::ref(editor), std::ref(disp));
    std::thread disp_thread([&]{ disp.accept_loop(editor); });

    editor.run();

    net_thread.detach();
    disp_thread.detach();

    return 0;
}
