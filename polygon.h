#ifndef POLYGON_H
#define POLYGON_H
#include "vector.h"
#include "phong.h"
#include "color.h"
#include "ray.h"
#include "texture.h"
#include "surface.h"
#include <string>
class polygon :public surface{
    private:
        vector* vertices;
        int size;
        vector normal;
        bool checkinside(vector point); 
    protected:
        void vector2barycentric(vector point, float& gamma, float& beta, float& alpha);
    public:
        polygon(vector* vectors_in, int size, vector normal, phong coefficients);
        ~polygon();
        bool intersect(ray ray_in, v_n& output) override;

};
class textured_polygon : public polygon{
    private :
        texture textures;
        vector tx;
        vector ty;
    public:
        textured_polygon(vector* vectors_in, int size, vector normal, phong coefficients, 
                std::string texture_path, float texture_coordinate[6]);
        color texture_color(vector vector_in) override;
};

#endif
