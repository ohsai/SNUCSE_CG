#include "sphere.h"
sphere::sphere(vector center, float radius,phong coefficients)
:surface(coefficients){
    this->center = center;
    this->radius = radius;
}
bool sphere::intersect(ray ray_in, v_n& output) 
{
    //check if it intersects
    vector c = center;
    vector o = ray_in.start;
    vector l = ray_in.direction; l = (1.0f/l.norm()) * l;
    float r = radius;
    float determinant = powf((l & (o - c)),2) 
        - (powf((o-c).norm(),2) - powf(r,2));
    if(determinant <0){
        return false;
    }
    //if it does, then find intersecting point
    float epsilon = 1e-3;
    float t = - (l & (o - c));
    float d1 = t + sqrt(determinant);
    float d2 = t - sqrt(determinant);
    float d;
    if((d1 > epsilon) && (d2 > epsilon)){
        d = fmin(d1,d2);
    }
    else if(d1>epsilon){
        d = d1;
    }
    else if(d2 > epsilon){
        d = d2;
    }
    else{
        return false;
    }
    vector intersecting_point = o + (d * l);
    output = v_n(intersecting_point, intersecting_point - c);
    return true;  
}

textured_sphere::textured_sphere (vector center, float radius, phong coefficients, 
    std::string texture_path)
    :sphere(center,radius,coefficients)

{
    this->textures = texture(texture_path);
}
color textured_sphere::texture_color(vector vector_in)
{
    //xyz to UV mapping
    vector n = (vector_in - center);
    n = (1.0f / n.norm()) * n;//normalize
    float u = atan2(n.coord[0], n.coord[2]) / (2 * M_PI) + 0.5f;
    float v = n.coord[1] * 0.5f + 0.5;
    //clamping
    int texture_x = fmin(fmax((int)(textures.width * u), 0), textures.width);
    int texture_y = fmin(fmax((int)(textures.height * v), 0), textures.height);
    return textures.pixelat(texture_x,texture_y);
}


