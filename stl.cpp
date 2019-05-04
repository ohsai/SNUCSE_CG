#include "stl.h"
single_stl_parser::single_stl_parser(float scale_factor, 
        float axis_angle[4], float translation[3],phong coeff){
    this->scale_factor = scale_factor;
    this->rotation = quaternion(axis_angle);
    this->translation = vector(translation);
    this->coefficients = coeff;
}
polygon* single_stl_parser::triangle(std::string normal, std::string vertex1, std::string vertex2, std::string vertex3,
            scene& total_scene){
    std::string header,header2, temp1,temp2,temp3;
    float coord[3];
    vector vnormal,vvertex1, vvertex2,vvertex3;
    vector* vertices = new vector[3];
    
    //parse normal
    std::stringstream nss(normal);
    nss>>header>>header2>>temp1>>temp2>>temp3;
    coord[0] = atof(temp1.c_str());
    coord[1] = atof(temp2.c_str());
    coord[2] = atof(temp3.c_str());
    vnormal = vector(coord);
    vnormal = rotation.rotate(vnormal); vnormal = (1.0f/vnormal.norm()) * vnormal;

    //parse first vertex
    std::stringstream v1ss(vertex1);
    v1ss>>header>>temp1>>temp2>>temp3;
    coord[0] = atof(temp1.c_str());
    coord[1] = atof(temp2.c_str());
    coord[2] = atof(temp3.c_str());
    vvertex1 = vector(coord);
    vvertex1 = (scale_factor * rotation.rotate(vvertex1)) + translation;
    vertices[0] = vvertex1;

    //parse second vertex
    std::stringstream v2ss(vertex2);
    v2ss>>header>>temp1>>temp2>>temp3;
    coord[0] = atof(temp1.c_str());
    coord[1] = atof(temp2.c_str());
    coord[2] = atof(temp3.c_str());
    vvertex2 = vector(coord);
    vvertex2 = (scale_factor * rotation.rotate(vvertex2)) + translation;
    vertices[1] = vvertex2;
    
    //parse thirc vertex
    std::stringstream v3ss(vertex3);
    v3ss>>header>>temp1>>temp2>>temp3;
    coord[0] = atof(temp1.c_str());
    coord[1] = atof(temp2.c_str());
    coord[2] = atof(temp3.c_str());
    vvertex3 = vector(coord);
    vvertex3 = (scale_factor * rotation.rotate(vvertex3)) + translation;
    vertices[2] = vvertex3;
    
    polygon* newp = new polygon(vertices, 3, vnormal, this->coefficients);
    return newp;
}
void single_stl_parser::stlobjectinsert(scene &total_scene, std::string stl_path){
    std::ifstream datafile(stl_path);
    if(datafile.fail()){
        std::cout<<"File does not exist. Abort."<<std::endl;
        exit(0);
    }
    std::string line;
    std::string temp;
    std::string normal;
    std::string v1;
    std::string v2;
    std::string v3;
    int order = 1;
    while(std::getline(datafile,line)){
        std::stringstream ss(line);
        ss>>temp;
        if(!temp.compare(std::string("facet"))){
            normal = line;
        }
        else if(!temp.compare(std::string("outer"))){
            order = 1;
        }
        else if(!temp.compare(std::string("endloop"))){
        }
        else if(!temp.compare(std::string("endfacet"))){
            polygon* p = triangle(normal,v1,v2,v3,total_scene);
            total_scene.insert_surface(p);
        }
        else if(!temp.compare(std::string("vertex"))){
            switch(order){
                case 1:
                    v1 = line;
                    break;
                case 2:
                    v2 = line;
                    break;
                case 3:
                    v3 = line;
                    break;
                default:
                    std::cout<<"stl vertices more than 3"<< std::endl;
            }
            order++;
        }
        else if(!temp.compare(std::string("solid"))){
        }
        else if(!temp.compare(std::string("endsolid"))){
            break;
        }
    }
}


//Implemented Quaternion
quaternion::quaternion(){
    index[0] = 0.0f;
    index[1] = 0.0f;
    index[2] = 0.0f;
    index[3] = 0.0f;
}

quaternion::quaternion(float axis_angle[4]){
    float aa[3] = {axis_angle[1], axis_angle[2], axis_angle[3]};
    vector a = vector(aa); 
    float angle = axis_angle[0]; a = (1.0f / a.norm()) * a;
    index[0] = cos(angle/2.0f);
    index[1] = a.coord[0] * sin(angle / 2.0f);
    index[2] = a.coord[1] * sin(angle / 2.0f);
    index[3] = a.coord[2] * sin(angle / 2.0f);
}
quaternion::quaternion(const vector& v_in){
    index[0] = 0.0f;
    index[1] = v_in.coord[0];
    index[2] = v_in.coord[1];
    index[3] = v_in.coord[2];
}
vector quaternion::rotate(const vector& v_in){
    quaternion p = quaternion(v_in);
    quaternion qinv = inv();
    quaternion q_out = mult(p.mult(qinv));
    float v_out[3] = {q_out.index[1], q_out.index[2], q_out.index[3]};
    return vector(v_out);
}
quaternion::quaternion(const quaternion& q_in){
    index[0] = q_in.index[0];
    index[1] = q_in.index[1];
    index[2] = q_in.index[2];
    index[3] = q_in.index[3];
}
quaternion quaternion::mult(const quaternion& q_right){
    quaternion q_out;
    q_out.index[0] = index[0] * q_right.index[0] - index[1] * q_right.index[1] - index[2] * q_right.index[2] - index[3] * q_right.index[3];
    q_out.index[1] = index[0] * q_right.index[1] + index[1] * q_right.index[0] + index[2] * q_right.index[3] - index[3] * q_right.index[2];
    q_out.index[2] = index[0] * q_right.index[2] - index[1] * q_right.index[3] + index[2] * q_right.index[0] + index[3] * q_right.index[1];
    q_out.index[3] = index[0] * q_right.index[3] + index[1] * q_right.index[2] - index[2] * q_right.index[1] + index[3] * q_right.index[0];
    return q_out;
}
quaternion quaternion::inv(){
    quaternion q_out;
    q_out.index[0] = index[0];
    q_out.index[1] = -index[1];
    q_out.index[2] = -index[2];
    q_out.index[3] = -index[3];
    return q_out;
}


