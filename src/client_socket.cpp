#include "client_socket.hpp"
#include <arpa/inet.h>
#include <cstdlib>

ClientSocket::ClientSocket(std::string ip, int port) : Socket(port), _ip(ip) {}

void ClientSocket::connect() {
    inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr);
    int res = ::connect(_fd, (struct sockaddr *)&_addr, sizeof(_addr));
    if (res < 0) { perror("connect"); exit(1); }
}

void ClientSocket::send(Message message) {
    Socket::send(_fd, message);
}

Message ClientSocket::receive() {
    return Socket::receive(_fd);
}
