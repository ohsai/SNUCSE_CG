#ifndef LIGHT_H
#define LIGHT_H
#include "vector.h"
#include "color.h"
#include <cmath>
class light{
    public:
        vector position;
        color intensity;
        color ambient_intensity;
        light();
        light(vector position, color intensity, color ambient_intensity);
        color intensity_atdist(float distance);
};
#endif
