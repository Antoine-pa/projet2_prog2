#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <string>
#include <sstream>

typedef enum { TEXT, ERROR, INFO, REQ} m_type;

class Message {
protected:
    std::string _content;
    m_type _type;
public:
    explicit Message(std::string content, m_type type);
    std::string get_content() const;
    m_type get_type() const;
    std::string to_string() const;
};

class Request : public Message {
    int _x;
    int _y;
    int _coord_r;
    int _coord_g;
    int _coord_b;
    void reload_content();
public:
    explicit Request(int x, int y, int r, int g, int b);
    int get_x() const;
    int get_y() const;
    int get_r() const;
    int get_g() const;
    int get_b() const;
};

#endif
