#include "socket.hpp"
#include <sys/socket.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

Socket::Socket(int port) : _port(port) {
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd < 0) { perror("socket"); exit(1); }
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
}

void Socket::close() {
    shutdown(_fd, SHUT_RDWR);
    ::close(_fd);
}

void Socket::send(int fd, Message message) {
    std::string s = message.to_string();
    const char *p = s.c_str();
    int todo = s.size();
    while (todo > 0) {
        int res = ::send(fd, p, todo, 0);
        if (res == -1) { perror("send"); exit(1); }
        p += res;
        todo -= res;
    }
}

Message Socket::receive(int fd) {
    char buff[512];
    int res = recv(fd, buff, 511, 0);
    if (res < 0) { perror("recv"); exit(1); }
    buff[res] = '\0';
    m_type type;
    if (res == 0)
        type = INFO; // connection closed by peer (EOF)
    else
        type = TEXT;
    return Message(buff, type);
}
