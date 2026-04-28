#include "image.hpp"

Image::Image(std::string name) {
    if (!sf::Image::loadFromFile(name)) {
        std::cout << "Could not load image " << name << std::endl;
        return;
    }
}

Image::Image() {}

sf::Vector2u Image::getSize() const {
    return sf::Image::getSize();
}

void Image::display(sf::RenderWindow& window) {
    sf::Vector2u size = getSize();
    int rows = size.y;
    int cols = size.x;
    int cellSize = 1;

    window.clear(sf::Color::Black);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(c * cellSize, r * cellSize);
            cell.setFillColor(getPixel(c, r));
            window.draw(cell);
        }
    }
}

Image Image::convolution(float_matrix ker) {
    Image result;
    sf::Vector2u size = getSize();

    int width = size.x;
    int height = size.y;

    result.create(width, height, sf::Color(0,0,0));

    int ker_width = ker[0].size();
    int ker_height = ker.size();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float acc_red = 0, acc_green = 0, acc_blue = 0;

            for (int ki = 0; ki < ker_height; ki++) {
                for (int kj = 0; kj < ker_width; kj++) {
                    int ix = x + kj - ker_width/2;
                    int iy = y + ki - ker_height/2;

                    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
                        sf::Color pixel = getPixel(ix, iy);
                        acc_red += ker[ki][kj] * pixel.r;
                        acc_green += ker[ki][kj] * pixel.g;
                        acc_blue += ker[ki][kj] * pixel.b;
                    }
                }
            }
            int r = std::max(0, std::min(255, (int)acc_red));
            int g = std::max(0, std::min(255, (int)acc_green));
            int b = std::max(0, std::min(255, (int)acc_blue));
            result.setPixel(x, y, sf::Color(r, g, b));
        }
    }

    return result;
}
