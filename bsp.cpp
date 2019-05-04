#include "bsp.h"
#include <cstdlib>
#include <ctime>

/*
 * Mesh : vector<vertex> vertex_list, vector<face> face_list;
 * vertex { 
 *	jhm::vector position;
 *	jhm::vector normal;
 * }
 * face {
 * 	int vertices[3];
 * 	material_type mt;
 * 	GLfloat opacity;
 * }
 *
 */


/*class BSPtree{
	private:
		node root;
		Mesh mesh;
	public:
*/
BSPtree::BSPtree(Mesh mesh_in){
	srand(time(nullptr));
	mesh = mesh_in;
	makeTree( mesh.face_list, &root);
}
jhm::vector BSPtree::normal_of_face(face face_chosen){
	jhm::vector face_chosen_normal = 
	normalize((mesh.vertex_list[face_chosen.vertices[2]].position - 
	mesh.vertex_list[face_chosen.vertices[1]].position)
	*(mesh.vertex_list[face_chosen.vertices[1]].position - 
	mesh.vertex_list[face_chosen.vertices[0]].position)
	);
	jhm::vector signvector =  (mesh.vertex_list[face_chosen.vertices[0]].position
	+ mesh.vertex_list[face_chosen.vertices[1]].position
	+ mesh.vertex_list[face_chosen.vertices[2]].position) / 3.0f;
	if(face_chosen_normal % signvector < 0){
		face_chosen_normal = -face_chosen_normal;
	}
	return face_chosen_normal;
}
int BSPtree::sgn(m_real input){
	if(input <0) return -1;
	else if(input<0) return 1;
	return 0;
}
void BSPtree::printvector(jhm::vector a){
	cout << a[0] << " " << a[1] << " " << a[2] <<endl;	
}
void BSPtree::makeTree(vector<face> cur_face_list,node* cur_node){
	int random = (cur_face_list.size() -1) * rand()/RAND_MAX;
	face face_chosen = cur_face_list[random];
	jhm::vector face_chosen_normal = face_chosen.normal;
	cur_face_list.erase(cur_face_list.begin() + random);
	vector<face> front_face_list;
	vector<face> rear_face_list;
	for(vector<face>::iterator i = cur_face_list.begin(); i!= cur_face_list.end(); ++i){
		m_real dot[3];
		jhm::vector temp;
		for(int j = 0; j<3; j++){
			dot[j] = (mesh.vertex_list[(*i).vertices[j]].position-mesh.vertex_list[face_chosen.vertices[0]].position) % face_chosen_normal;
		}
		int done_flag = 0;
		if((sgn(dot[0]) == sgn( dot[1])) &&(sgn(dot[0]) == sgn( dot[2]) )){
			if(sgn(dot[2]) >=0)
			{
				front_face_list.push_back(*i);
			}
			else
			{
				rear_face_list.push_back(*i);
			}
			done_flag = 1;
		}
		if(done_flag <1){
			for( int j = 0; j<3; j++){
				int a = j;
				int b = (j+1)%3;
				int c = (j+2)%3;
				if(sgn(dot[a]) == 0){
					if(sgn(dot[b]) == sgn(dot[c])){
						if(sgn(dot[b]) >0)
							front_face_list.push_back(*i);
						else
							rear_face_list.push_back(*i);	
					}
					else if(sgn(dot[b]) == 0){
						if(sgn(dot[c]) >0)
							front_face_list.push_back(*i);
						else
							rear_face_list.push_back(*i);		
					}
					else if(sgn(dot[c]) == 0){
						if(sgn(dot[b]) >0)
							front_face_list.push_back(*i);
						else
							rear_face_list.push_back(*i);	
					}
					else{
						jhm::vector plane_v = mesh.vertex_list[face_chosen.vertices[0]].position;
						vertex v1 = mesh.vertex_list[(*i).vertices[b]];
						vertex v2 = mesh.vertex_list[(*i).vertices[c]];
						m_real t3 = ((plane_v - v1.position) % face_chosen_normal)/
						((v2.position - v1.position) % face_chosen_normal);
						vertex v3 = {interpolate(t3,v1.position,v2.position),interpolate(t3,v1.normal,v2.normal)};
						int v3_loc = mesh.vertex_list.size();
						mesh.vertex_list.push_back(v3);
						face tri1 = {{(*i).vertices[a], (*i).vertices[b], v3_loc},(*i).normal,(*i).mt, (*i).opacity};
						face tri2 = {{(*i).vertices[a], v3_loc,(*i).vertices[c]},(*i).normal,(*i).mt, (*i).opacity};
						if(sgn(dot[b])>=0){
							front_face_list.push_back(tri1);
							rear_face_list.push_back(tri2);
						}
						else{
							front_face_list.push_back(tri2);
							rear_face_list.push_back(tri1);
						}
					}
					done_flag = 1;
					break;
				}
			}
		}
		if(done_flag <1){
			for( int j= 0; j<3; j++){
				int a = j;
				int b = (j+1)%3;
				int c = (j+2)%3;
				if(sgn(dot[b]) == sgn(dot[c])){
				jhm::vector plane_v = mesh.vertex_list[face_chosen.vertices[0]].position;
				vertex v0 = mesh.vertex_list[(*i).vertices[a]];
				vertex v1 = mesh.vertex_list[(*i).vertices[b]];
				vertex v2 = mesh.vertex_list[(*i).vertices[c]];
				m_real t3 = ((plane_v - v0.position) % face_chosen_normal)/
				((v1.position - v0.position) % face_chosen_normal);
				vertex v3 = {interpolate(t3,v0.position,v1.position),interpolate(t3,v0.normal,v1.normal)};
				m_real t4 = ((plane_v - v0.position) % face_chosen_normal)/
				((v2.position - v0.position) % face_chosen_normal);
				vertex v4 = {interpolate(t4,v0.position,v2.position),interpolate(t4,v0.normal,v2.normal)};
				int v3_loc = mesh.vertex_list.size();
				mesh.vertex_list.push_back(v3);
				int v4_loc = mesh.vertex_list.size();
				mesh.vertex_list.push_back(v4);
				face tri1 = {{(*i).vertices[b], (*i).vertices[c], v3_loc},(*i).normal,(*i).mt, (*i).opacity};
				face tri2 = {{(*i).vertices[c], v3_loc,v4_loc},(*i).normal,(*i).mt, (*i).opacity};
				face tri3 = {{(*i).vertices[a], v3_loc,v4_loc},(*i).normal,(*i).mt, (*i).opacity};
				if(sgn(dot[a]) <0){
					front_face_list.push_back(tri1);
					front_face_list.push_back(tri2);
					rear_face_list.push_back(tri3);
				}
				else{
					rear_face_list.push_back(tri1);
					rear_face_list.push_back(tri2);
					front_face_list.push_back(tri3);
				}
				done_flag = 1;
				break;
				}
			}	
		}
	}
	cur_node->cur_face = face_chosen;
	if(front_face_list.size() >0){
		cur_node->right = (node*)malloc(sizeof(node));
		makeTree(front_face_list, cur_node->right);
	}
	else{
		cur_node->right = NULL;
	}
	if(rear_face_list.size() >0){
		cur_node->left = (node*)malloc(sizeof(node));
		makeTree(rear_face_list, cur_node->left);
	}
	else{
		cur_node->left = NULL;
	}
}
void BSPtree::render (jhm::vector eye){
	render(eye, &root);
}
void BSPtree::render(jhm::vector eye, node* cur_node){
	vertex vx_temp = mesh.vertex_list[cur_node->cur_face.vertices[0]];
	jhm::vector face_normal = cur_node->cur_face.normal;
	if((eye - vx_temp.position) % face_normal > 0){
		if(cur_node->left != NULL){
			render(eye, cur_node->left);
		}
		
	glBegin(GL_TRIANGLES);
		setMaterial(cur_node->cur_face.mt, cur_node->cur_face.opacity);
		vertex vertex1 = mesh.vertex_list[cur_node->cur_face.vertices[0]];
		vertex vertex2 = mesh.vertex_list[cur_node->cur_face.vertices[1]];
		vertex vertex3 = mesh.vertex_list[cur_node->cur_face.vertices[2]];
		glNormal3f(vertex1.normal[0],vertex1.normal[1],vertex1.normal[2]);
		glVertex3f(vertex1.position[0], vertex1.position[1], vertex1.position[2]);
		glNormal3f(vertex2.normal[0],vertex2.normal[1],vertex2.normal[2]);
		glVertex3f(vertex2.position[0], vertex2.position[1], vertex2.position[2]);
		glNormal3f(vertex3.normal[0],vertex3.normal[1],vertex3.normal[2]);
		glVertex3f(vertex3.position[0], vertex3.position[1], vertex3.position[2]);
	glEnd();
		if(cur_node->right != NULL){
			render(eye, cur_node->right);
		}
	}
	else if((eye - vx_temp.position) % face_normal <0){
		if(cur_node->right != NULL){
			render(eye, cur_node->right);
		}
	glBegin(GL_TRIANGLES);
		setMaterial(cur_node->cur_face.mt, cur_node->cur_face.opacity);
		vertex vertex1 = mesh.vertex_list[cur_node->cur_face.vertices[0]];
		vertex vertex2 = mesh.vertex_list[cur_node->cur_face.vertices[1]];
		vertex vertex3 = mesh.vertex_list[cur_node->cur_face.vertices[2]];
		glNormal3f(vertex1.normal[0],vertex1.normal[1],vertex1.normal[2]);
		glVertex3f(vertex1.position[0], vertex1.position[1], vertex1.position[2]);
		glNormal3f(vertex2.normal[0],vertex2.normal[1],vertex2.normal[2]);
		glVertex3f(vertex2.position[0], vertex2.position[1], vertex2.position[2]);
		glNormal3f(vertex3.normal[0],vertex3.normal[1],vertex3.normal[2]);
		glVertex3f(vertex3.position[0], vertex3.position[1], vertex3.position[2]);
	glEnd();
		if(cur_node->left != NULL){
			render(eye, cur_node->left);
		}
	}
	else{
		if(cur_node->left != NULL){
			render(eye, cur_node->left);
		}
		if(cur_node->right != NULL){
			render(eye, cur_node->right);
		}
	}
}


