#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include "image.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_image> [convolution]" << std::endl;
        return -1;
    }

    std::string conv_name = "identity";
    if (argc >= 3)
        conv_name = argv[2];

    std::map<std::string, float_matrix> kernels = {
        {"identity", {{0,0,0},{0,1,0},{0,0,0}}},
        {"blur",     {{1/9.0f,1/9.0f,1/9.0f},{1/9.0f,1/9.0f,1/9.0f},{1/9.0f,1/9.0f,1/9.0f}}},
        {"sharpen",  {{0,-1,0},{-1,5,-1},{0,-1,0}}},
        {"edge",     {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}}}
    };

    if (kernels.find(conv_name) == kernels.end()) {
        std::cerr << "Unknown convolution: " << conv_name << std::endl;
        return 1;
    }

    Image img(argv[1]);
    Image img2 = img.convolution(kernels[conv_name]);
    img2.display();

    return 0;
}
