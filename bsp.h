#include "model.h"
#ifndef BSP_H
#define BSP_H
struct node{
	face cur_face;
	node* left;
	node* right;
};
class BSPtree{
	private:
		node root;
		Mesh mesh;
	public:
		BSPtree(Mesh mesh_in);
		jhm::vector normal_of_face(face face_chosen);
		int sgn(m_real input);
		void printvector(jhm::vector a);
		void makeTree(vector<face> cur_face_list,node* cur_node);
		void render (jhm::vector eye);
		void render(jhm::vector eye, node* cur_node);
};


#endif
