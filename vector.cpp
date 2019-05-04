#include "vector.h"

vector::vector(float coord[3]){
    this->coord[0] = coord[0];
    this->coord[1] = coord[1];
    this->coord[2] = coord[2];
}
vector::vector(){
    coord[0] = 0.0f;
    coord[1] = 0.0f;
    coord[2] = 0.0f;
}
vector::vector(const vector& v2){
    this->coord[0] = v2.coord[0];
    this->coord[1] = v2.coord[1];
    this->coord[2] = v2.coord[2];
}
float vector::norm(){
    return sqrtf(
            coord[0] * coord[0] 
            + coord[1] * coord[1] 
            + coord[2] * coord[2] 
         );  
}
float operator&(const vector& v1, const vector& v2){
    return v1.coord[0] * v2.coord[0]
            + v1.coord[1] * v2.coord[1]
            + v1.coord[2] * v2.coord[2];
}
vector operator+(const vector& v1, const vector& v2){
    float coord_out[3];
    coord_out[0] = v1.coord[0] + v2.coord[0];
    coord_out[1] = v1.coord[1] + v2.coord[1];
    coord_out[2] = v1.coord[2] + v2.coord[2];
    return vector(coord_out);
}
vector operator%(const vector& v1, const vector& v2){
    float coord_out[3];
    coord_out[0] = v1.coord[1] * v2.coord[2] - v1.coord[2] * v2.coord[1];
    coord_out[1] = v1.coord[2] * v2.coord[0] - v1.coord[0] * v2.coord[2];
    coord_out[2] = v1.coord[0] * v2.coord[1] - v1.coord[1] * v2.coord[0];
    return vector(coord_out);
}
vector operator*(const float& f1, const vector& v2){
    float coord_out[3];
    coord_out[0] = f1 * v2.coord[0];
    coord_out[1] = f1 * v2.coord[1];
    coord_out[2] = f1 * v2.coord[2];
    return vector(coord_out);
}
vector operator-(const vector& v1, const vector& v2){
    float coord_out[3];
    coord_out[0] = v1.coord[0] - v2.coord[0];
    coord_out[1] = v1.coord[1] - v2.coord[1];
    coord_out[2] = v1.coord[2] - v2.coord[2];
    return vector(coord_out);
}
vector vector::operator-(){
    float coord_out[3];
    coord_out[0] = -coord[0];
    coord_out[1] = -coord[1];
    coord_out[2] = -coord[2];
    return vector(coord_out);
}
bool vector::isparallel(vector v2){
    float epsilon = 1e-4;
    return fabs(((*this) & v2) / ((*this).norm() * v2.norm())) > (1 - epsilon);
}
v_n::v_n(float coord[3], float normal[3])
{
    this->coord[0] = coord[0];
    this->coord[1] = coord[1];
    this->coord[2] = coord[2];
    this->normal[0] = normal[0];
    this->normal[1] = normal[1];
    this->normal[2] = normal[2];

}
v_n::v_n(vector v_in, vector normal)
{
    this->coord[0] = v_in.coord[0];
    this->coord[1] = v_in.coord[1];
    this->coord[2] = v_in.coord[2];
    this->normal[0] = normal.coord[0];
    this->normal[1] = normal.coord[1];
    this->normal[2] = normal.coord[2];
    
}
v_n::v_n(){
    this->coord[0] = 0.0f;
    this->coord[1] = 0.0f;
    this->coord[2] = 0.0f;
    this->normal[0] = 0.0f;
    this->normal[1] = 0.0f;
    this->normal[2] = 0.0f;
}
v_n::v_n(const v_n& vn2){
    this->coord[0] = vn2.coord[0];
    this->coord[1] = vn2.coord[1];
    this->coord[2] = vn2.coord[2];
    this->normal[0] = vn2.normal[0];
    this->normal[1] = vn2.normal[1];
    this->normal[2] = vn2.normal[2];
}

