#ifndef SCENE_H
#define SCENE_H
#include <list>
#include "surface.h"
#include "ray.h"
#include "vector.h"
#include "phong.h"

class scene{
    private:
        std::list<surface*> surflist;
    public:
        scene();
        ~scene();
        bool intersects_first(ray ray_in, v_n * point_out, surface*& surf_out);
        void insert_surface(surface* surf_in);
};

#endif 
