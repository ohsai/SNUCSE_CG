#include "basicgl.h"
#ifndef MODEL_H
#define MODEL_H
void drawReference();
void drawCR(list<cs> csl);
void drawBSpline(list<cs> csl,m_real scalar = 1, jhm::quater quaternion = jhm::quater(1,0,0,0), jhm::vector translation = jhm::vector(0,0,0));
void makeMesh(void);
enum material_type {ruby, gold, silver, bronze, pearl, jade, plastic,none};
void setMaterial(material_type mt,GLfloat opacity);

typedef struct vertex_struct {
	jhm::vector position;
	jhm::vector normal;
} vertex;
typedef int index;
typedef struct face_struct {
	index vertices[3];
	jhm::vector normal;
	material_type mt;
	GLfloat opacity;
} face;
class Mesh
{
	private:
	public :
	vector<vertex> vertex_list;
	vector<face> face_list;
	Mesh();
	void insert_triangle(jhm::vector vertices[3], jhm::vector face_normal, material_type material, GLfloat opacity = 1.0f);
	void drawMesh(void);
};

extern Mesh newMesh;
//void drawMesh(void);
void drawCube(material_type mt,GLfloat opacity);
void drawCube_transparent();
#endif
