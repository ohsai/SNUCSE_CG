#include "basicgl.h"

typedef struct {float x,y;} vector2;
typedef struct {float x,y,z;} vector3;
typedef struct {float w,x,y,z;} quaternion;


extern float camera_x , camera_z;
extern float camera_y;
extern float lookat_x;
extern float lookat_y;
extern float lookat_z;
extern float up_x , up_y , up_z ;

extern float camera_distance;
extern float cam_dist_coeff ; 
extern float zoom_factor ;
extern double perspective_fov ;
extern double perspective_aspect;
extern double perspective_znear ;
extern double perspective_zfar ;
extern vector2 xyo;
extern vector2 xy ;

vector3 cross_product(vector3 a, vector3 b);
float vector3_dot_product(vector3 a, vector3 b);
quaternion quaternion_multiply(quaternion a, quaternion b);
float vector3_norm(vector3 v);
quaternion quaternion_conjugate(quaternion a);
vector3 scalar_vector3(vector3 v, float s);
vector3 vector3_normalize(vector3 v);
vector3 vector3_sum(vector3 a, vector3 b);
vector3 view2sphere(vector2 input);
vector2 vector2_subtract(vector2 a, vector2 b);
void cameraWork();
void mouseButton(int button, int state, int x, int y) ;
void mouseMove(int x, int y);
void handleKeypress(unsigned char key, int x, int y);
void handleArrowPress(int key, int x, int y);
void zoom(float zoom_factor_input);
