#include "ray.h"
ray::ray(vector start, vector direction){
    this->start = start;
    this->direction = direction;
}
ray::ray(const ray & r2){
    start = r2.start;
    direction = r2.direction;
}

