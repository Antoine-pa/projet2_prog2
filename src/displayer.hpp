#ifndef DISPLAYER_HPP
#define DISPLAYER_HPP

#include "client_socket.hpp"
#include <string>
#include <vector>
#include <tuple>

class Displayer {
    ClientSocket _cs;
    std::string _buf;

    std::string read_line();

public:
    Displayer(const std::string& ip, int port);
    ~Displayer();

    std::pair<int,int> get_canvas_size();
    std::vector<std::tuple<int,int,int,int,int>> receive_initial_canvas();
    std::tuple<int,int,int,int,int> receive_update();
};

#endif
