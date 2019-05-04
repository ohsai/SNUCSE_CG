#include "camera.h"
camera::camera(float pos[3],float lookat[3], float upvector[3]){
    this->position = vector(pos);
    vector P_0(pos);
    vector P_ref(lookat);
    vector N = P_0 - P_ref;
    this->n = (1.0f / (N.norm())) * N;
    vector V(upvector);
    this->u = (1.0f/ V.norm()) * (V % this->n);

    this->v = this->n % this->u;
    std::cout<<"cam.u : " << u.coord[0] <<" "<< u.coord[1] <<" "<< u.coord[2] << std::endl;
    std::cout<<"cam.v : " << v.coord[0] <<" "<< v.coord[1] <<" "<< v.coord[2] << std::endl;
}
