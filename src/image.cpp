#include "image.hpp"

Image::Image(std::string name) {
    if (!_texture.loadFromFile(name)) {
        std::cout << "Could not load texture " << name << std::endl;
    }
}

Image::Image() {}

void Image::display() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "display image");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        sf::Sprite image;
        image.setTexture(_texture);
        image.setPosition(sf::Vector2f(0,0));
        image.scale(sf::Vector2f(1,1.5));
        window.clear();
        window.draw(image);

        window.display();
    }
}


Image Image::convolution(int_matrix ker) {
    return Image();
}