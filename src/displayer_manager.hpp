#ifndef DISPLAYER_MANAGER_HPP
#define DISPLAYER_MANAGER_HPP

#include "serveur_socket.hpp"
#include "image_editor.hpp"
#include <vector>
#include <mutex>

class DisplayerManager {
    ServeurSocket _ss;
    std::vector<int> _displayer_fds;
    std::mutex _mutex;

    void send_line(int fd, const std::string& line);
    void send_initial_canvas(int client_fd, ImageEditor& editor);

public:
    DisplayerManager(int port);
    void accept_loop(ImageEditor& editor);
    void broadcast(int x, int y, int r, int g, int b);
};

#endif
