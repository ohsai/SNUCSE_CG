#include "scene.h"

scene::scene(){
}
bool scene::intersects_first(ray ray_in, v_n * point_out, surface*& surf_out){
    v_n temp;
    v_n closest_point;
    surface* surf_temp;
    int found = 0;
    for(std::list<surface*>::iterator it = surflist.begin(); it != surflist.end(); ++it){
        if((*it)->intersect(ray_in, temp)){
            if(found == 0)
            {
                closest_point = temp;
                surf_temp = (*it);
                found = 1;
            }
            else{
                float dist1 = (vector(temp.coord) - ray_in.start).norm();
                float dist2 = (vector(closest_point.coord) - ray_in.start).norm();
                if(dist1 < dist2){
                    closest_point = temp;
                    surf_temp = (*it);
                }
            }
        }
    }
    if(found == 0){
        return false;
    }
    else{
        *point_out = closest_point;
        surf_out = surf_temp;
        return true;    
    }
}
scene::~scene(){
    for(std::list<surface*>::iterator it = surflist.begin(); it != surflist.end(); ++it){
        delete (*it);
    }
}
void scene::insert_surface(surface* surf_in){
    surflist.push_back(surf_in);
    return;
}

