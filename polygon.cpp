#include "polygon.h"

polygon::polygon(vector* vectors_in, int size, vector normal, phong coefficients)
:surface(coefficients)
{
    vertices = new vector[size];
    for(int i = 0; i<size; i++){
        vertices[i] = vectors_in[i];
    }
    this->size = size;
    this->normal = normal;
}
polygon::~polygon(){
    delete[] vertices;
}
bool polygon::intersect(ray ray_in, v_n& output){
    float epsilon = 1e-3;
    //check plane-ray parallel
    if((ray_in.direction & normal) == 0.0f){
        return false;
    }
    //intersection with plane
    float t = (normal & (vertices[0] - ray_in.start)) / (normal & ray_in.direction);
    if(t < epsilon){
        return false;
    }
    output = v_n(ray_in.start + t * ray_in.direction,normal);
    //check if it is inside polygon
    return checkinside(vector(output.coord));
    /*
    if(checkinside(vector(output.coord))){
        return true;
    }
    else{
        return false;
    }
    */

}
void polygon::vector2barycentric(vector point, float& gamma, float& beta, float& alpha){
    vector u = vertices[1] - vertices[0];
    vector v = vertices[2] - vertices[0];
    vector n = u % v;
    vector w = point - vertices[0];
    gamma = ((u % w) & n) / (n & n);
    beta = ((w % v) & n) / (n & n);
    alpha = 1.0f - gamma - beta;
}
bool polygon::checkinside(vector point){
    float gamma,beta,alpha;
    //suppose polygon is triangle
    vector2barycentric(point,gamma,beta,alpha);

    if(
            (0.0f <= alpha)&&(alpha<=1.0f)
            &&(0.0f <= beta)&&(beta<=1.0f)
            &&(0.0f <= gamma)&&(gamma<=1.0f)
      ){
        return true;
    }
    else{
        return false;
    }
}
textured_polygon::textured_polygon(vector* vectors_in, int size, vector normal, phong coefficients, 
                std::string texture_path, float texture_coordinate[6])
                :polygon(vectors_in, size, normal, coefficients)
{
        textures = texture(texture_path);
        float txf[3] = {texture_coordinate[0], texture_coordinate[2], texture_coordinate[4]};
        float tyf[3] = {texture_coordinate[1], texture_coordinate[3], texture_coordinate[5]};
        tx = vector(txf); //a.tx b.tx c.tx
        ty = vector(tyf); //a.ty b.ty c.ty
}
color textured_polygon::texture_color(vector vector_in){

    //UV mapping
    float abc[3];
    vector2barycentric(vector_in, abc[0], abc[1], abc[2]);
    vector bary(abc);
    float x_img = bary & tx;
    float y_img = bary & ty;
    return textures.pixelat(x_img,y_img);
}
