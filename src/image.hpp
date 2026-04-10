#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <vector>

using int_matrix = std::vector<std::vector<int>>;

class Image {
    public:
        Image();
        void display();
        Image convolution(int_matrix ker);
};

#endif
