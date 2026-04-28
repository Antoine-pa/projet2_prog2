#ifndef IMAGE_EDITOR_HPP
#define IMAGE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <string>

class ImageEditor {
private:
    sf::Image _image;           
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::RenderWindow _window;
    sf::Color _paintColor;   

    void updateTexture();
    void handleInput();       
    void processEvents();     

public:
    explicit ImageEditor(const std::string& filepath);
    void run();
};

#endif