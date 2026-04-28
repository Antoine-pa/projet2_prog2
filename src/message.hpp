#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <string>

typedef enum { TEXT, ERROR, INFO, REQ} m_type;

class Message {
    std::string _content;
    m_type _type;
public:
    explicit Message(std::string content, m_type type);
    std::string get_content() const;
    m_type get_type() const;
    std::string to_string() const;
};

class Request : public Message {
    int _coord_r;
    int _coord_g;
    int _coord_b;
    int _x;
    int _y;
public:
    explicit Request(int r, int g, int b, int x, int y);
    int get_r() const;
    int get_g() const;
    int get_b() const;
    int get_x() const;
    int get_y() const;
};

#endif
