#include "displayer_manager.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

DisplayerManager::DisplayerManager(int port) : _ss(port) {
    _ss.bind();
    _ss.listen();
    std::cerr << "[Displayer] En ecoute sur le port " << port << "\n";
}

void DisplayerManager::send_line(int fd, const std::string& line) {
    std::string data = line + "\n";
    const char* p = data.c_str();
    int todo = data.size();
    while (todo > 0) {
        int n = ::send(fd, p, todo, 0);
        if (n <= 0) return;
        p += n; todo -= n;
    }
}

void DisplayerManager::send_initial_canvas(int client_fd, ImageEditor& editor) {
    auto size = editor.get_size();
    send_line(client_fd, std::to_string(size.x) + " " + std::to_string(size.y));
    for (auto [x, y, r, g, b] : editor.get_snapshot())
        send_line(client_fd, std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(r)+" "+std::to_string(g)+" "+std::to_string(b));
    send_line(client_fd, "END");
}

void DisplayerManager::accept_loop(ImageEditor& editor) {
    while (true) {
        int client_fd = ::accept(_ss.get_fd(), nullptr, nullptr);
        if (client_fd < 0) continue;
        send_initial_canvas(client_fd, editor);
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _displayer_fds.push_back(client_fd);
        }
        std::cerr << "[Displayer] Nouvel afficheur connecte\n";
    }
}

void DisplayerManager::broadcast(int x, int y, int r, int g, int b) {
    std::string line = std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(r)+" "+std::to_string(g)+" "+std::to_string(b)+"\n";
    std::lock_guard<std::mutex> lock(_mutex);
    std::vector<int> alive;
    for (int fd : _displayer_fds) {
        if (::send(fd, line.c_str(), line.size(), 0) > 0)
            alive.push_back(fd);
        else
            ::close(fd);
    }
    _displayer_fds = alive;
}
