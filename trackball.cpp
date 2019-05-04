#include "trackball.h"

float camera_x = 5.0f;
float camera_z = 5.0f;
float camera_y = 1.2f;
float lookat_x = 0.0f;
float lookat_y = 1.2f;
float lookat_z = 0.0f;
float up_x = 0.0f, up_y = 1.0f, up_z = 0.0f;
float camera_distance = sqrt(camera_x * camera_x + camera_y * camera_y + camera_z * camera_z);
float cam_dist_coeff = 0; 
float zoom_factor = 0;
double perspective_fov = 45.0;
double perspective_aspect;
double perspective_znear = 1.0;
double perspective_zfar = 500.0;
vector2 xyo = (vector2){-1,-1};
vector2 xy = (vector2){-1,-1};

vector3 cross_product(vector3 a, vector3 b){
	return (vector3){a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}
float vector3_dot_product(vector3 a, vector3 b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
quaternion quaternion_multiply(quaternion a, quaternion b){
	return (quaternion){a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
                      a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
                      a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
                      a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w};
}
float vector3_norm(vector3 v){
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
quaternion quaternion_conjugate(quaternion a){
	return (quaternion){a.w, -a.x, -a.y, -a.z};
}
vector3 scalar_vector3(vector3 v, float s){
	return (vector3){s * v.x,s * v.y,s * v.z};
}
vector3 vector3_normalize(vector3 v){
	float norm = vector3_norm(v);
	return (vector3){v.x/norm,v.y/norm,v.z/norm};
}
vector3 vector3_sum(vector3 a, vector3 b){
	return (vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}
vector3 view2sphere(vector2 input){
	vector3 mouseup = (vector3){up_x,up_y,up_z};
	vector3 through = (vector3){camera_x-lookat_x, camera_y - lookat_y, camera_z - lookat_z};
	vector3 mouseright = vector3_normalize(cross_product(through,mouseup));
	mouseup = vector3_normalize(mouseup);
	return vector3_sum(through,vector3_sum(scalar_vector3(mouseup,input.y * 0.1f),scalar_vector3(mouseright, input.x * 0.1f)));
}
vector2 vector2_subtract(vector2 a, vector2 b){
	return (vector2){a.x - b.x, a.y - b.y};
}

void cameraWork(){
	vector3 so = (vector3){camera_x-lookat_x, camera_y - lookat_y, camera_z - lookat_z};
	vector3 s = view2sphere(vector2_subtract(xy,xyo));
	vector3 axis = cross_product(so,s);
	float theta = acos(vector3_dot_product(scalar_vector3(so , 1.0f/vector3_norm(so)),scalar_vector3(s,1.0f/vector3_norm(s))));
	axis = vector3_normalize(axis);
	quaternion rotate_q = (quaternion){cos(theta/2), sin(theta/2) * axis.x, sin(theta/2) * axis.y, sin(theta/2) * axis.z};
	quaternion cam_quat = (quaternion){0,camera_x-lookat_x, camera_y-lookat_y, camera_z-lookat_z};
	quaternion up_quat = (quaternion){0,up_x, up_y, up_z};
	cam_quat = quaternion_multiply(quaternion_multiply(rotate_q , cam_quat),quaternion_conjugate(rotate_q));
	up_quat = quaternion_multiply(quaternion_multiply(rotate_q , up_quat),quaternion_conjugate(rotate_q));
	camera_x = cam_quat.x + lookat_x;
	camera_y = cam_quat.y + lookat_y;
	camera_z = cam_quat.z + lookat_z;
	up_x = up_quat.x;
	up_y = up_quat.y;
	up_z = up_quat.z;
	xyo = xy;
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON || button == GLUT_LEFT_BUTTON){
		if(state == GLUT_UP){
			xy = xyo;
		}
		else{
			xyo = (vector2){x,y};
			xy = xyo;
		}
	}
	else if(button==3){
		zoom_factor -= 1.0f;
		zoom(zoom_factor);
	}
	else if(button==4){
		zoom_factor += 1.0f;
		zoom(zoom_factor);
	}
}
void mouseMove(int x, int y){
		xy = (vector2){x,y};
		if((xy.x != xyo.x) || (xy.y != xyo.y)){
			cameraWork();
		}
		xyo = xy;
}
void handleKeypress(unsigned char key, int x, int y){
	switch(key){
		case 27: 
			exit(0);
		case 13:
			camera_x = 5.0f + lookat_x;
			camera_y = 0.0f + lookat_y;
			camera_z = 5.0f + lookat_z;
			up_x = 0.0f;
			up_y = 1.0f;
			up_z = 0.0f;
			camera_distance = vector3_norm((vector3){5.0f, 1.0f, 5.0f});
			cam_dist_coeff = 0.0f;
			zoom_factor = 0.0f;
			perspective_fov = 45.0f;
			
	}
}
void handleArrowPress(int key, int x, int y){
	switch(key){	
		case GLUT_KEY_UP:
			cam_dist_coeff -= 1.0f;
			break;
		case GLUT_KEY_DOWN:	
			cam_dist_coeff += 1.0f;
			break;
	}
	vector3 camera_direction = vector3_normalize((vector3){camera_x - lookat_x, camera_y - lookat_y, camera_z - lookat_z});
	vector3 new_camera = scalar_vector3(camera_direction,camera_distance * exp(cam_dist_coeff/10.0f));
	camera_x = new_camera.x + lookat_x;
	camera_y = new_camera.y + lookat_y;
	camera_z = new_camera.z + lookat_z;
}

void zoom(float zoom_factor_input){
	float fov = 180.0f * 1.0f/(1.0f + exp(-zoom_factor_input/100.0f + 1.09861));
	perspective_fov = fov;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(perspective_fov, perspective_aspect, perspective_znear, perspective_zfar);
}



