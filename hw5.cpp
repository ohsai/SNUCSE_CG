#include <iostream>
#include "window.h"
#include "sphere.h"
#include "polygon.h"
#include "stl.h"
#include "config.h"
using namespace std;

void rendering_main_loop(window& window_in,light * lights,int number_of_lights, scene& total_scene);
void scene_formation(scene& total_scene,char* stl_datapath);
void light_formation(light* lights);
int main(int argc, char** argv){
    //argv[1] is path to stl file
    if(argc != 2) {
        std::cout<<"Usage : ./hw5 [path to stlfile]"<<std::endl;
        return 1;
    }
    
    //decide window specification
    window window_instance(IMAGE_WIDTH,IMAGE_HEIGHT);
    //create light sources
    int number_of_lights = 2;
    light lights[number_of_lights];
    light_formation(lights);
    //create scene
    scene total_scene;
    scene_formation(total_scene, argv[1]);
    //rendering main loop
    rendering_main_loop(window_instance,lights,number_of_lights, total_scene);
	if(VERBOSE){
        printf("Rendered png saved at %s\n", PNG_EXPORT_PATH);
    }
    return 0;
}
void rendering_main_loop(window& window_in,light * lights,int number_of_lights, scene& total_scene){
    //setup camera
    float pos[3] = {4.0f,2.0f,2.0f};
    float look[3] = {0.0f,0.8f,0.5f};
    float up[3] = {0.0f, 1.0f, 0.0f};
    camera cam(pos,look,up);
	//shoot ray and trace each of them
    window_in.rendering(cam,lights,number_of_lights,total_scene); 
    //display each pixel
    window_in.export_pixels();
}
void light_formation(light* lights){
    {
    float pos[3] = {0.0f,3.0f,0.0f};
    float intens[3] = {0.6f,0.6f,0.6f};
    float ambint[3] = {0.2f,0.2f,0.2f};
    lights[0] = light(vector(pos),color(intens),color(ambint));
    }
    {
    float pos[3] = {0.0f,3.0f,0.0f};
    float intens[3] = {0.6f,0.6f,0.6f};
    float ambint[3] = {0.2f,0.2f,0.2f};
    lights[1] = light(vector(pos),color(intens),color(ambint));
    }
}
void scene_formation(scene& total_scene, char* stl_datapath){
    //create floating water sphere
    sphere* s1;
    {
    float ambcoef[3]={0.1f,0.1f,0.1f};
    float difcoef[3]={0.1f,0.1f,0.1f};
    float specoef[3]={0.5f,0.5f,0.5f};
    phong s1_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.4,
            0.05f,
            0.9f,
            1.3f);
    float possp[3] = {0.0f,1.0f,1.0f};
    s1 = new sphere(vector(possp),0.5f,s1_phong);
    }
    //create globe
    sphere* s2;
    {
    float ambcoef[3]={0.39125f,0.39125f,0.39125f};
    float difcoef[3]={0.70754f,0.70754f,0.70754f};
    float specoef[3]={0.7083f,0.7083f,0.7083f};
    phong s2_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.4,
            0.0f,
            //0.0f,
            0.0f,
            1.333f);
    float possp[3] = {0.25f,0.75f,2.25f};
    s2 = new textured_sphere(vector(possp),0.5f,s2_phong,std::string(SPHERE_TEXTURE_PATH));
    }
    //import stl object
    {
        float ambcoef[3]={0.00f,0.1f,0.06f};
        float difcoef[3]={0.00f,0.51f,0.51f};
        float specoef[3]={0.502f,0.502f,0.502f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.25,
            0.0f,
            0.0f,
            1.333f);
        float axis_angle[4] = {3.141592f,-0.7071f,0.7071f,0.0f};
        float translation[3] = {0.7f,0.23f,0.0f};
        single_stl_parser parser2 = single_stl_parser(0.22f, axis_angle, translation, s3_phong);
        parser2.stlobjectinsert(total_scene, string(stl_datapath));
    }
    //
    polygon* p2;
    {
        float v1[3] = {1.0f,0.0f,0.0f};
        float v2[3] = {0.0f,-1.0f,0.0f};
        float v3[3] = {0.0f,0.0f,1.0f};
        int size = 3;
        float normal[3] = {1.0f,-1.0f,1.0f};
        float ambcoef[3]={0.9215f,0.1745f,0.1215f};
        float difcoef[3]={0.07568f,0.61424f,0.07568f};
        float specoef[3]={0.633f,0.727811f,0.633f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            0.05f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p2 = new polygon(vertices,size,nv,s3_phong);
    }
    polygon* p3;
    {
        float v1[3] = {3.0f,0.0f,-0.5f};
        float v2[3] = {-1.0f,3.0f,-0.5f};
        float v3[3] = {-1.0f,0.0f,-0.5f};
        int size = 3;
        float normal[3] = {0.0f,0.0f,1.0f};
        float ambcoef[3]={0.0f,0.0f,0.0f};
        float difcoef[3]={0.0f,0.0f,0.0f};
        float specoef[3]={0.9f,0.9f,0.9f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            1.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p3 = new polygon(vertices,size,nv,s3_phong);
    }
    polygon* p4;
    {
        float v1[3] = {-1.0f,0.0f,3.0f};
        float v2[3] = {-1.0f,3.0f,-0.5f};
        float v3[3] = {-1.0f,0.0f,-0.5f};
        int size = 3;
        float normal[3] = {1.0f,0.0f,0.0f};
        float ambcoef[3]={0.1f,0.1f,0.1f};
        float difcoef[3]={0.3f,0.3f,0.3f};
        float specoef[3]={0.9f,0.9f,0.9f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            1.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p4 = new polygon(vertices,size,nv,s3_phong);
    }
    polygon* p5;
    {
        float v1[3] = {-1.0f,0.0f,3.0f};
        float v2[3] = {-1.0f,3.0f,-0.5f};
        float v3[3] = {-1.0f,3.0f,3.0f};
        int size = 3;
        float normal[3] = {1.0f,0.0f,0.0f};
        float ambcoef[3]={0.1f,0.1f,0.1f};
        float difcoef[3]={0.3f,0.3f,0.3f};
        float specoef[3]={0.9f,0.9f,0.9f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            1.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p5 = new polygon(vertices,size,nv,s3_phong);
    }
    polygon* p6;
    {
        float v1[3] = {3.0f,0.0f,-0.5f};
        float v2[3] = {-1.0f,3.0f,-0.5f};
        float v3[3] = {3.0f,3.0f,-0.5f};
        int size = 3;
        float normal[3] = {0.0f,0.0f,1.0f};
        float ambcoef[3]={0.0f,0.0f,0.0f};
        float difcoef[3]={0.0f,0.0f,0.0f};
        float specoef[3]={0.9f,0.9f,0.9f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            1.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p6 = new polygon(vertices,size,nv,s3_phong);
    }
    polygon* p7;
    {
        float v1[3] = {-1.0f,0.0f,-0.5f};
        float v2[3] = {-1.0f,0.0f,3.0f};
        float v3[3] = {3.0f,0.0f,-0.5f};
        int size = 3;
        float normal[3] = {0.0f,1.0f,0.0f};
        float ambcoef[3]={0.2f,0.2f,0.2f};
        float difcoef[3]={0.4f,0.4f,0.4f};
        float specoef[3]={0.9f,0.9f,0.9f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            0.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p7 = new polygon(vertices,size,nv,s3_phong);
    }
    polygon* p8;
    {
        float v1[3] = {3.0f,0.0f,3.0f};
        float v2[3] = {-1.0f,0.0f,3.0f};
        float v3[3] = {3.0f,0.0f,-0.5f};
        int size = 3;
        float normal[3] = {0.0f,1.0f,0.0f};
        float ambcoef[3]={0.2f,0.2f,0.2f};
        float difcoef[3]={0.4f,0.4f,0.4f};
        float specoef[3]={0.9f,0.9f,0.9f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            0.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p8 = new polygon(vertices,size,nv,s3_phong);
    }
    polygon* p9;
    {
        float v1[3] = {-1.0f,0.0f,3.0f};
        float v2[3] = {3.0f,0.0f,3.0f};
        float v3[3] = {-1.0f,3.0f,3.0f};
        int size = 3;
        float normal[3] = {0.0f,0.0f,-1.0f};
        float ambcoef[3]={0.1f,0.1f,0.1f};
        float difcoef[3]={0.2f,0.2f,0.2f};
        float specoef[3]={0.5f,0.5f,0.5f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            0.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        float t_cor[6]={ 
                        1,1,
                        1280,769,
                        1,769
                        };
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p9 = new textured_polygon(vertices,size,nv,s3_phong,
                    std::string(WALL_TEXTURE_PATH),t_cor);
    }
    polygon* p10;
    {
        float v1[3] = {3.0f,0.0f,3.0f};
        float v2[3] = {-1.0f,3.0f,3.0f};
        float v3[3] = {3.0f,3.0f,3.0f};
        int size = 3;
        float normal[3] = {0.0f,0.0f,-1.0f};
        float ambcoef[3]={0.1f,0.1f,0.1f};
        float difcoef[3]={0.2f,0.2f,0.2f};
        float specoef[3]={0.5f,0.5f,0.5f};
        phong s3_phong(
            color(ambcoef),
            color(difcoef),
            color(specoef),
            180*0.6,
            0.0f,
            0.0f,
            1.333f);
        vector* vertices = new vector[3];
        vertices[0] = vector(v1);
        vertices[1] = vector(v2);
        vertices[2] = vector(v3);
        float t_cor[6]={ 
                        1,769,
                        1280,769,
                        1,1
                        };
        vector nv = vector(normal); nv = (1.0f/nv.norm()) * nv;
            p10 = new textured_polygon(vertices,size,nv,s3_phong,
                    std::string(WALL_TEXTURE_PATH),t_cor);
    }
    total_scene.insert_surface(p3);//right mirror1
    total_scene.insert_surface(p4);//rear mirror1
    total_scene.insert_surface(p5);//rear mirror2
    total_scene.insert_surface(p6);//right mirror2
    total_scene.insert_surface(p7);//floor1
    total_scene.insert_surface(p8);//floor2
    total_scene.insert_surface(p9);//left brick wall1
    total_scene.insert_surface(p10);//left brick wall2
    total_scene.insert_surface(s1);//refractive water sphere
    total_scene.insert_surface(s2);//globe  sphere
}
