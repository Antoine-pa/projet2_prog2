#include <SFML/Graphics.hpp>
#include <iostream>
#include "image.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_image>" << std::endl;
        return -1;
    }
    Image img = Image(argv[1]);
    img.display();

    return 0;
}