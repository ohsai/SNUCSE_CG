#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "ray.h"
#include "color.h"
#include "vector.h"
#include "scene.h"
#include "light.h"
#include "phong.h"
#include "surface.h"
#include <list>
#define MAX_RAYTRACE_RECURSION 5
class ray_tracer{
    private:
    public:
        ray_tracer(){}
        static ray reflect(ray ray_in, vector normal, vector reflected_point);
        static ray refract(ray ray_in, vector normal, 
            vector refracted_point,
            float refraction_coefficient_1,
            float refraction_coefficient_2);
        static color phong_illumination(ray ray_in, vector normal,vector point, phong coefficients, light& light_in,bool not_shadowed);
        static color tracer(ray ray_in, scene& total_scene,light* lights, int number_of_lights, int recursion_depth);
};

#endif
