#include "message.hpp"

Message::Message(std::string content, m_type type) : _content(content), _type(type) {}

std::string Message::get_content() const { return _content; }
m_type Message::get_type() const { return _type; }
std::string Message::to_string() const { return _content; }

Request::Request(int x, int y, int r, int g, int b) : Message("", REQ), _x(x), _y(y), _coord_r(r), _coord_g(g), _coord_b(b) {
    reload_content();
}

void Request::reload_content() {
    std::ostringstream oss;
    oss << _x << ":" << _y << ":" << _coord_r << ":" << _coord_g << ":" << _coord_b;
    _content = oss.str();
}

int Request::get_x() const {return _x;}
int Request::get_y() const {return _y;}
int Request::get_r() const {return _coord_r;}
int Request::get_g() const {return _coord_g;}
int Request::get_b() const {return _coord_b;}