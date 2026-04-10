#ifndef IMAGE_HPP
#define IMAGE_HPP

class Image {
    public:
        Image();
        void display();
        Image convolution(int* ker, int n);
};

#endif
