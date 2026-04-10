#include "serveur_socket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>

ServeurSocket::ServeurSocket(int port) : Socket(port), _client_fd(-1) {
    int on = 1;
    int res = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (res < 0) { perror("setsockopt"); exit(1); }
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void ServeurSocket::bind() {
    int res = ::bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr));
    if (res < 0) { perror("bind"); exit(1); }
}

void ServeurSocket::listen() {
    int res = ::listen(_fd, SOMAXCONN);
    if (res < 0) { perror("listen"); exit(1); }
}

void ServeurSocket::accept() {
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    _client_fd = ::accept(_fd, (struct sockaddr *)&cli_addr, &clilen);
    if (_client_fd < 0) { perror("accept"); exit(1); }
}

void ServeurSocket::send(Message message) {
    Socket::send(_client_fd, message);
}

Message ServeurSocket::receive() {
    return Socket::receive(_client_fd);
}

void ServeurSocket::close_client() {
    shutdown(_client_fd, SHUT_RDWR);
    ::close(_client_fd);
}
