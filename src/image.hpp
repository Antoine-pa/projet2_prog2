#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <iostream>

using float_matrix = std::vector<std::vector<float>>;

class Image : sf::Image {
    sf::Texture _texture;
    public:
        Image();
        Image(std::string name);
        void display();
        Image convolution(float_matrix ker);
};

#endif
