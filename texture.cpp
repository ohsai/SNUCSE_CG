#include "texture.h"
#include <iostream>
texture::texture(std::string texture_path){
    img = new CImg<unsigned char>(texture_path.c_str());
    width = img->width();
    height = img->height();
    std::cout<<"Trying :" <<(float)((*img)(317,158,0,0)) <<" width : " << width << " height : " << height<<std::endl;
    
}
texture::~texture(){
}
texture::texture(){
    img = NULL;
    width = 0;
    height = 0;
}
texture::texture(const texture& t2){
    img = t2.img;
    width = t2.width;
    height = t2.height;
}
color texture::pixelat(int x, int y){
    float rgb_out[3];
    rgb_out[0] = (float)((*img)(x,y,0,0)) * (1.0f/255.0f);
    rgb_out[1] = (float)((*img)(x,y,0,1)) * (1.0f/255.0f);
    rgb_out[2] = (float)((*img)(x,y,0,2)) * (1.0f/255.0f);
    return color(rgb_out);
}
