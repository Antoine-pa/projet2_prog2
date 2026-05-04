#ifndef IMAGE_EDITOR_HPP
#define IMAGE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <mutex>

class ImageEditor {
private:
    sf::Image _image;           
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::RenderWindow _window;
    std::mutex _mutex; 

    void updateTexture();
    void processEvents();     

public:
    explicit ImageEditor(unsigned int width = 800, unsigned int height = 600);
    
    void run();
    bool update_pixel_from_request(int x, int y, int r, int g, int b);
    sf::Vector2u get_size() const;
    std::vector<std::tuple<int,int,int,int,int>> get_snapshot();
};

#endif