#ifndef TEXTURE_H
#define TEXTURE_H
#include <CImg.h>
#include <string>
#include "color.h"
using namespace cimg_library;
class texture{
    private:
        CImg<unsigned char>* img;
    public:
        texture(std::string texture_path);
        texture();
        texture(const texture& t2);
        ~texture();
        color pixelat(int x, int y);
        int width;
        int height;
};

#endif
