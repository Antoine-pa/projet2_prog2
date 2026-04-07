#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <stdio>
#include <iostream>

typedef enum {
    TEXT,
    ERROR,
    INFO
} m_type;

class Message {
    std::string _content;
    m_type _type;
    public:
        explicit Message(std::string content, m_type type) //param à def
        std::string get_content() const;
        m_type get_type() const;
        std::string to_string() const;
};

#endif