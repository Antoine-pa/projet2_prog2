#include "message.hpp"

Message::Message(std::string content, m_type type) : _content(content), _type(type) {}

std::string Message::get_content() const { return _content; }
m_type Message::get_type() const { return _type; }
std::string Message::to_string() const { return _content; }
