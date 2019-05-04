#ifndef SPHERE_H
#define SPHERE_H
#include "vector.h"
#include "surface.h"
#include "phong.h"
#include "ray.h"
#include "texture.h"
#include "color.h"
#include <cmath>
class sphere : public surface{
    protected:
	    vector center;
	    float radius;
	public:
	    sphere(vector center, float radius,phong coefficients);
	    bool intersect(ray ray_in,v_n& output) override;
};
class textured_sphere : public sphere{
    private:
        texture textures;
    public:
        textured_sphere (vector center, float radius, phong coefficients, 
                std::string texture_path);//, vector texture_coordinate);
        color texture_color(vector vector_in) override;
};

#endif
