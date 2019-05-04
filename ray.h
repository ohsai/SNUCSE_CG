#ifndef RAY_H
#define RAY_H
#include "vector.h"
class ray{
    public:
        vector start;
        vector direction;

        ray(vector start, vector direction);
        ray(const ray & r2);
};

#endif
