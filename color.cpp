#include "color.h"
color::color(){
    this->rgb[0] = 0.0f;
    this->rgb[1] = 0.0f;
    this->rgb[2] = 0.0f;
}
color::color(float rgb[3]){
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
}
color::color(const color &c2){
    rgb[0] = c2.rgb[0];
    rgb[1] = c2.rgb[1];
    rgb[2] = c2.rgb[2];
}
color operator& (const color& c1, const color& c2){
    float rgb_out[3];
    rgb_out[0] = c1.rgb[0] * c2.rgb[0];
    rgb_out[1] = c1.rgb[1] * c2.rgb[1];
    rgb_out[2] = c1.rgb[2] * c2.rgb[2];
    return color(rgb_out);
}
color operator+ (const color& c1, const color& c2){
    float rgb_out[3];
    rgb_out[0] = c1.rgb[0] + c2.rgb[0];
    rgb_out[1] = c1.rgb[1] + c2.rgb[1];
    rgb_out[2] = c1.rgb[2] + c2.rgb[2];
    return color(rgb_out);
}
color operator*(const float& f1, const color& c2){
    float rgb_out[3];
    rgb_out[0] = f1 * c2.rgb[0];
    rgb_out[1] = f1 * c2.rgb[1];
    rgb_out[2] = f1 * c2.rgb[2];
    return color(rgb_out);
}
