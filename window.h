#ifndef WINDOW_H
#define WINDOW_H
#include "ray_tracer.h"
#include "camera.h"
#include <pngwriter.h>
class window{
    private:
        float fovy;
        float aspect;
        ray_tracer ray_tracer_instance;
    public:
        int width;
        int height;
        float *pixels;
        window(int width, int height);
        ~window();
        bool rendering(camera& cam, 
                light* lights, int number_of_lights,
                scene& total_scene);
        ray ray_casting(camera& cam,int pixel_x, int pixel_y);
        void export_pixels(void);
};
#endif
