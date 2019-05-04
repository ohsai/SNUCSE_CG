#include "vector.h"
#include "phong.h"
#include "scene.h"
#include <string>
#include <sstream>
#include <fstream>
#include "polygon.h"

class quaternion{
    private:
        float index[4];
    public:
        quaternion();
        quaternion(float axis_angle[3]);
        quaternion(const vector& v_in);
        quaternion(const quaternion& q_in);
        vector rotate(const vector& v_in);
        quaternion mult(const quaternion& q_right);
        quaternion inv();
};
class single_stl_parser{
    private:
        float scale_factor;
        quaternion rotation;
        vector translation;
        phong coefficients;
    public:
    single_stl_parser(float scale_factor, float axis_angle[4], float translation[3],phong coeff);
    polygon* triangle(std::string normal, std::string vertex1, std::string vertex2, std::string vertex3,
            scene &total_scene);// parse single polygon and return polygon
    void stlobjectinsert(scene &total_scene, std::string stl_path); //insert total stl polygons    
};
