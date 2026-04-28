#include "client.hpp"
#include <iostream>

Client::Client(std::string ip, int port) : _cs(ip, port) {}

void Client::run() {
    _cs.connect();
    int rolls[] = {6, 20, 100};
    for (int n : rolls) {
        _cs.send(Message("roll " + std::to_string(n), TEXT));
        Message reply = _cs.receive();
        std::cout << "roll " << n << " -> " << reply.to_string() << "\n";
    }
    _cs.send(Message("unknown", TEXT));
    Message err = _cs.receive();
    std::cout << "unknown cmd -> " << err.to_string() << "\n";
    _cs.close();
}