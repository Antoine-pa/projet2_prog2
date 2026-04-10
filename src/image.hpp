#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <iostream>

using int_matrix = std::vector<std::vector<int>>;

class Image {
    sf::Texture _texture;
    public:
        Image();
        Image(std::string name);
        void display();
        Image convolution(int_matrix ker);
};

#endif
