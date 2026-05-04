#include "image_editor.hpp"

ImageEditor::ImageEditor(unsigned int width, unsigned int height)
{
    _image.create(width, height, sf::Color::White);
    updateTexture();

    _window.create(sf::VideoMode(width, height), "Pixel Editor - Reseau");
    _window.setFramerateLimit(60); 
}

void ImageEditor::updateTexture() {
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture);
}

void ImageEditor::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }
}

bool ImageEditor::update_pixel_from_request(int x, int y, int r, int g, int b) {
    sf::Vector2u size = _image.getSize();
    if (x < 0 || (unsigned int)x >= size.x || y < 0 || (unsigned int)y >= size.y)
        return false;
    std::lock_guard<std::mutex> lock(_mutex);
    _image.setPixel(x, y, sf::Color(r, g, b));
    updateTexture();
    return true;
}

sf::Vector2u ImageEditor::get_size() const {
    return _image.getSize();
}

std::vector<std::tuple<int,int,int,int,int>> ImageEditor::get_snapshot() {
    std::lock_guard<std::mutex> lock(_mutex);
    std::vector<std::tuple<int,int,int,int,int>> result;
    auto size = _image.getSize();
    for (unsigned int y = 0; y < size.y; y++) {
        for (unsigned int x = 0; x < size.x; x++) {
            sf::Color c = _image.getPixel(x, y);
            if (c.r != 255 || c.g != 255 || c.b != 255)
                result.emplace_back(x, y, c.r, c.g, c.b);
        }
    }
    return result;
}

void ImageEditor::run() {
    while (_window.isOpen()) {
        processEvents();

        _window.clear();
        
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _window.draw(_sprite); 
        }
        
        _window.display();
    }
}