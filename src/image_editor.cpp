#include "image_editor.hpp"
#include <iostream>

ImageEditor::ImageEditor(const std::string& filepath)
    : _paintColor(sf::Color::Red) 
{
    // Chargement direct du fichier dans l'éditeur
    if (!_image.loadFromFile(filepath)) {
        std::cerr << "Erreur: Impossible de charger l'image " << filepath << "\n";
    }
    updateTexture();

    sf::Vector2u size = _image.getSize();
    _window.create(sf::VideoMode(size.x, size.y), "Pixel Editor - Clic gauche pour peindre");
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

void ImageEditor::handleInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        sf::Vector2u size = _image.getSize();

        // Modification directe de l'objet sf::Image de SFML
        if (mousePos.x >= 0 && (unsigned int)mousePos.x < size.x &&
            mousePos.y >= 0 && (unsigned int)mousePos.y < size.y) {
            
            _image.setPixel(mousePos.x, mousePos.y, _paintColor);
            updateTexture(); // Rafraîchit la texture affichée
        }
    }
}

void ImageEditor::run() {
    while (_window.isOpen()) {
        processEvents();
        handleInput();

        _window.clear();
        _window.draw(_sprite); 
        _window.display();
    }
}