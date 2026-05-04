#include "client.hpp"
#include <iostream>

Client::Client(std::string ip, int port) : _cs(ip, port) {}

void Client::send(const Message& msg) {
    _cs.send(msg);
}

Message Client::receive() {
    return _cs.receive();
}

void Client::connect() {
    _cs.connect();
}

void Client::close() {
    _cs.close();
}

std::pair<int,int> Client::get_canvas_size() {
    _cs.connect();
    _cs.send(Message("size", TEXT));
    Message response = _cs.receive();
    _cs.close();
    int w = 0, h = 0;
    std::istringstream iss(response.to_string());
    iss >> w >> h;
    return {w, h};
}

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