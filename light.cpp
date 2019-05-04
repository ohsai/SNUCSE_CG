#include "light.h"
light::light(vector position, color intensity, color ambient_intensity){
    this->position = position;
    this->intensity = intensity;
    this->ambient_intensity = intensity;
}
light::light(){
    float pos[3] = {1.0f,0.0f,0.0f};
    float intense[3] = {0.1f,0.1f,0.1f};
    float ambint[3] = {0.1f,0.1f,0.1f};
    this->position = vector(pos);
    this->intensity = 
        color(intense);
    this->ambient_intensity = 
        color(ambint);
}
color light::intensity_atdist(float distance){
    return fmin(1.0f, 1.0f/((distance / 25.0f +1.0f) * (distance/25.0f+1.0f))) * intensity;
}
