#include "client.hpp"
#include "message.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage : " << argv[0] << " <port> size\n";
        std::cerr << "        " << argv[0] << " <port> <x> <y> <r> <g> <b>\n";
        return 1;
    }

    try {
        int port = std::stoi(argv[1]);
        Client client("127.0.0.1", port);

        if (argc == 3 && std::string(argv[2]) == "size") {
            auto [w, h] = client.get_canvas_size();
            std::cout << w << " " << h << "\n";
        } else if (argc == 7) {
            std::string payload = std::string(argv[2]) + " " + argv[3] + " " + argv[4] + " " + argv[5] + " " + argv[6];
            client.connect();
            client.send(Message(payload, REQ));
            Message reponse = client.receive();
            std::cout << reponse.to_string() << "\n";
        } else {
            std::cerr << "Usage : " << argv[0] << " <port> size\n";
            std::cerr << "        " << argv[0] << " <port> <x> <y> <r> <g> <b>\n";
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "[Erreur] " << e.what() << "\n";
        return 1;
    }

    return 0;
}