#ifndef PHONG_H
#define PHONG_H
#include "color.h"
class phong{
    public:
        color ambient_coeff;
        color diffuse_coeff;
        color specular_coeff;
        float shininess_coeff;
        float reflection_coefficient;
        float refraction_coefficient;
        float refract_index;

        phong();
        phong(const color& ambient_coeff, 
                const color& diffuse_coeff, 
                const color& specular_coeff, 
                float shininess_coeff,
                float reflection_coefficient,
                float refraction_coefficient,
                float refract_index);
        phong(const phong & p2);
};

#endif
