#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"
class camera{
    public:
        vector position;
        vector n;
        vector u;
        vector v;
        camera(float pos[3],float lookat[3], float upvector[3]);

};
#endif
