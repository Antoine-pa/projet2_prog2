#include "client.hpp"
#include <iostream>

Client::Client(std::string ip, int port) : _cs(ip, port) {}

void Client::run() {
    _cs.connect();
    std::string line;
    while (std::getline(std::cin, line))
        _cs.send(Message(line, TEXT));
    _cs.close();
}
