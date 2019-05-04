#include "surface.h"
surface::surface(phong coefficients){
    this->coefficients = coefficients;
}
bool surface::intersect(ray ray_in, v_n& output){
    return false;
}
color surface::texture_color(vector vector_in){ //overrideed surface method
    float rgb[3] = {1.0f,1.0f,1.0f};
    return color(rgb);
}
