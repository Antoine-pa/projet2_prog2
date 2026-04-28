#include "message.hpp"

Message::Message(std::string content, m_type type) : _content(content), _type(type) {}

std::string Message::get_content() const { return _content; }
m_type Message::get_type() const { return _type; }
std::string Message::to_string() const { return _content; }

Request::Request(int r, int g, int b, int x, int y) : Message("", REQ), _coord_r(r), _coord_g(g), _coord_b(b), _x(x), _y(y) {}

int Request::get_r() const {return _coord_r;}
int Request::get_g() const {return _coord_g;}
int Request::get_b() const {return _coord_b;}
int Request::get_x() const {return _x;}
int Request::get_y() const {return _y;}