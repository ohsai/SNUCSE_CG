#include "window.h"
#include "config.h"
window::window(int width, int height){
    this->width = width;
    this->height = height;
    fovy = 90; // degree 90 fovy
    aspect = ((float) width) /((float) height);
    ray_tracer_instance = ray_tracer();
    pixels = new float[this->width * this->height * 3];
}
window::~window(){
    delete[] pixels;
}

bool window::rendering(camera& cam, light* lights, int number_of_lights,scene& total_scene){ 
    for(int i = 0; i<width; i++){
        for(int j = 0; j<height; j++){
            if(VERBOSE){
                std::cout<<"Rendering (" << i << " , " <<j <<")-th pixel"<<std::endl;
            }
            color temp = ray_tracer_instance.tracer(ray_casting(cam, i,j),
                    total_scene,lights, number_of_lights,0);
            this->pixels[i* (this->height*3) + j * 3 + 0] = temp.rgb[0];
            this->pixels[i* (this->height*3) + j * 3 + 1] = temp.rgb[1];
            this->pixels[i* (this->height*3) + j * 3 + 2] = temp.rgb[2];
        }
    }
}
ray window::ray_casting(camera& cam, int pixel_x, int pixel_y){
    vector start_temp = cam.position;
    float y_angle = tan(fovy/2.0f * M_PI / 180.0f);
    float x_angle = y_angle * aspect;
    vector direction_temp = (-1.0f * cam.n)
    + 
    (((float)(pixel_x - width/2))/((float)width) * x_angle ) 
    * cam.u
    + (((float)(pixel_y - height/2))/((float)height) * y_angle) 
    * cam.v;
    return ray(start_temp, direction_temp);
}
void window::export_pixels(void){
    pngwriter image(this->width, this->height, 0.0, PNG_EXPORT_PATH);
    for(int i = 0; i<this->width; i++){
        for(int j = 0; j < this->height; j++){
            double r = (double)this->pixels[i*(this->height*3) + j*3 + 0];
            double g = (double)this->pixels[i*(this->height*3) + j*3 + 1];
            double b = (double)this->pixels[i*(this->height*3) + j*3 + 2];
            image.plot(i,j,r,g,b);
        }
    }
    image.close();
    return;
}

