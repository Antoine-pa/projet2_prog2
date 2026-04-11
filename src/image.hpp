#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using float_matrix = std::vector<std::vector<float>>;

class Image : sf::Image {
    public:
        Image();
        Image(std::string name);
        sf::Vector2u getSize() const;
        void display(sf::RenderWindow& window);
        Image convolution(float_matrix ker);
};

#endif
