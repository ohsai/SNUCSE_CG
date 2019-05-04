#include "phong.h"
phong::phong(const color& ambient_coeff, const color& diffuse_coeff, 
        const color& specular_coeff, float shininess_coeff,
        float reflection_coefficient, float refraction_coefficient,
        float refract_index){
   
    this->ambient_coeff = ambient_coeff;
    this->diffuse_coeff = diffuse_coeff;
    this->specular_coeff = specular_coeff;
    this->shininess_coeff = shininess_coeff;
    this->reflection_coefficient = reflection_coefficient;
    this->refraction_coefficient = refraction_coefficient;
    this->refract_index = refract_index;
}
phong::phong(){
    float rgb[3] = {0.0f,0.0f,0.0f};
    this->ambient_coeff = color(rgb);
    this->diffuse_coeff = color(rgb);
    this->specular_coeff = color(rgb);
    this->shininess_coeff = 1;
    this->reflection_coefficient = 0.0f;
    this->refraction_coefficient = 0.0f;
    this->refract_index = 1.0;
} //black default constructor
phong::phong(const phong & p2){
    ambient_coeff = p2.ambient_coeff;
    diffuse_coeff = p2.diffuse_coeff;
    specular_coeff = p2.specular_coeff;
    shininess_coeff = p2.shininess_coeff;
    reflection_coefficient = p2.reflection_coefficient;
    refraction_coefficient = p2.refraction_coefficient;
    refract_index = p2.refract_index;
}
