#include "client.hpp"

Client::Client(std::string ip, int port) : _cs(ip, port) {}

void Client::run() {
    _cs.connect();
    _cs.send(Message("HELLO", TEXT));
    _cs.close();
}
