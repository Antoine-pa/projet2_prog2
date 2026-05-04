#include "displayer.hpp"
#include "image_editor.hpp"
#include <thread>
#include <iostream>

void reception_updates(Displayer& displayer, ImageEditor& editor) {
    while (true) {
        auto [x, y, r, g, b] = displayer.receive_update();
        editor.update_pixel_from_request(x, y, r, g, b);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }
    int port = std::stoi(argv[1]);

    Displayer displayer("127.0.0.1", port + 1);

    auto [w, h] = displayer.get_canvas_size();
    ImageEditor editor(w, h);

    for (auto [x, y, r, g, b] : displayer.receive_initial_canvas())
        editor.update_pixel_from_request(x, y, r, g, b);

    std::thread net_thread(reception_updates, std::ref(displayer), std::ref(editor));

    editor.run();

    net_thread.detach();
    return 0;
}
