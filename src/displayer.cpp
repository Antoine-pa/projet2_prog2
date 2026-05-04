#include "displayer.hpp"
#include <sys/socket.h>
#include <cstdlib>
#include <sstream>

Displayer::Displayer(const std::string& ip, int port) : _cs(ip, port) {
    _cs.connect();
}

Displayer::~Displayer() {
    _cs.close();
}

std::string Displayer::read_line() {
    int fd = _cs.get_fd();
    while (true) {
        auto pos = _buf.find('\n');
        if (pos != std::string::npos) {
            std::string line = _buf.substr(0, pos);
            _buf = _buf.substr(pos + 1);
            return line;
        }
        char tmp[256];
        int n = ::recv(fd, tmp, sizeof(tmp), 0);
        if (n <= 0) return "";
        _buf.append(tmp, n);
    }
}

std::pair<int,int> Displayer::get_canvas_size() {
    int w = 0, h = 0;
    std::istringstream(read_line()) >> w >> h;
    return {w, h};
}

std::vector<std::tuple<int,int,int,int,int>> Displayer::receive_initial_canvas() {
    std::vector<std::tuple<int,int,int,int,int>> pixels;
    while (true) {
        std::string line = read_line();
        if (line == "END") break;
        int x, y, r, g, b;
        std::istringstream(line) >> x >> y >> r >> g >> b;
        pixels.emplace_back(x, y, r, g, b);
    }
    return pixels;
}

std::tuple<int,int,int,int,int> Displayer::receive_update() {
    int x, y, r, g, b;
    std::istringstream(read_line()) >> x >> y >> r >> g >> b;
    return {x, y, r, g, b};
}
