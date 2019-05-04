#ifndef SURFACE_H
#define SURFACE_H
#include "phong.h"
#include "ray.h"
#include "color.h"
#include "vector.h"
class surface{
    public:
        phong coefficients;
        surface(phong coefficients);
        virtual bool intersect(ray ray_in, v_n& output);
        virtual color texture_color(vector vector_in); 
};

#endif
