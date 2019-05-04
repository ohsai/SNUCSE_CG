#include "model.h"
//model
float N = 10;
float M = 10;

cs drawCRpoint(float t, cs p_m1, cs p_0, cs p_1, cs p_2){
	float t3 = t * t * t;
	float t2 = t * t;
	float B_m1 = ((-1) * t3 + 2 * t2 - 1 * t)/2.0;
	float B_0 = (3 * t3 - 5 * t2 + 2 * 1)/2.0;
	float B_1 = (-3 * t3 + 4 * t2 + 1 * t)/2.0;
	float B_2 = (1 * t3 -1 * t2)/2.0;
	float x = B_m1 * p_m1.first + B_0 * p_0.first + B_1 * p_1.first + B_2 * p_2.first;
	float y = B_m1 * p_m1.second + B_0 * p_0.second + B_1 * p_1.second + B_2 * p_2.second;
	cs output = make_pair(x,y);
	return output;
}
cs drawBSplinepoint(float t, cs p_0, cs p_1, cs p_2, cs p_3){
	float t3 = t * t * t;
	float t2 = t * t;
	float B_0 = (-1 * t3 + 3 * t2 - 3 * t + 1)/6.0;
	float B_1 = (3 * t3 - 6 * t2 + 4)/6.0;
	float B_2 = (- 3 * t3 + 3 * t2 + 3 * t + 1)/6.0;
	float B_3 = (t3)/6.0;
	float x = B_0 * p_0.first + B_1 * p_1.first + B_2 * p_2.first + B_3 * p_3.first;
	float y = B_0 * p_0.second + B_1 * p_1.second + B_2 * p_2.second + B_3 * p_3.second;
	cs output = make_pair(x,y);
	return output;
}
void drawCR(list< cs > csl){
	if(csl.size() < 2) return;
	cs p_m1 = csl.back();
	cs p_endp1 = csl.front();
	cs p_endp2 = (*std::next(csl.begin()));
	csl.push_front(p_m1);
	csl.push_back(p_endp1);
	csl.push_back(p_endp2);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f,0.0f,0.0f);
	for(list< cs >::iterator csl_it = std::next(csl.begin());csl_it != std::prev(std::prev(csl.end())); ++csl_it){
		cs cur_p_m1 = *std::prev(csl_it);
		cs cur_p_0 = *csl_it;
		cs cur_p_1 = *std::next(csl_it);
		cs cur_p_2 = *std::next(std::next(csl_it));
		for(float t = 0.0; t <= 1.0; t = t + 1.0/N){
			cs point_at_t = drawCRpoint(t,cur_p_m1,cur_p_0,cur_p_1,cur_p_2);
			glVertex3f(point_at_t.first,0,point_at_t.second);	
		}
	}
	glEnd();
	
}
list<jhm::vector> CR_vertices(list< cs > csl, m_real scalar , jhm::quater quaternion , jhm::vector translation ){
	if(csl.size() < 2) {
		cout<< "Not enough length for vector interpolation"<<endl;
		exit(1);}
	cs p_m1 = csl.back();
	cs p_endp1 = csl.front();
	cs p_endp2 = (*std::next(csl.begin()));
	csl.push_front(p_m1);
	csl.push_back(p_endp1);
	csl.push_back(p_endp2);
	list<jhm::vector> output;
	for(list< cs >::iterator csl_it = std::next(csl.begin());csl_it != std::prev(std::prev(csl.end())); ++csl_it){
		cs cur_p_m1 = *std::prev(csl_it);
		cs cur_p_0 = *csl_it;
		cs cur_p_1 = *std::next(csl_it);
		cs cur_p_2 = *std::next(std::next(csl_it));
		for(float t = 0.0; t <= 1.0; t = t + 1.0/N){
			cs point_at_t = drawCRpoint(t,cur_p_m1,cur_p_0,cur_p_1,cur_p_2);
			jhm::vector temp = jhm::vector(point_at_t.first, 0, point_at_t.second);
			temp = rotate(quaternion,scalar * temp) + translation;
			output.push_back(temp);
		}
	}
	return output;
	
}
void drawBSpline(list< cs > csl, m_real scalar , jhm::quater quaternion , jhm::vector translation ){
	if(csl.size() < 4) return;
	csl.push_back(csl.front());
	csl.push_back(*std::next(csl.begin()));
	csl.push_back(*std::next(std::next(csl.begin())));
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f,1.0f,0.0f);
	for(list< cs >::iterator csl_it = csl.begin(); csl_it != std::prev(std::prev(std::prev(csl.end()))); ++csl_it){
		cs cur_p_0 = *csl_it;
		cs cur_p_1 = *std::next(csl_it);
		cs cur_p_2 = *std::next(std::next(csl_it));
		cs cur_p_3 =*std::next(std::next(std::next(csl_it)));
		for(float t = 0.0; t <= 1.0; t = t + 1.0/N){
			cs point_at_t = drawBSplinepoint(t,cur_p_0,cur_p_1,cur_p_2,cur_p_3);
			jhm::vector temp = jhm::vector(point_at_t.first, 0, point_at_t.second);
			temp = rotate(quaternion,scalar * temp) + translation;
			glVertex3f(temp[0], temp[1] ,temp[2]);
		}
	}
	glEnd();
}
list<jhm::vector> BSpline_vertices(list< cs > csl, m_real scalar , jhm::quater quaternion , jhm::vector translation ){
	if(csl.size() < 4) {
		cout<< "Not enough length for vector interpolation"<<endl;
		exit(1);}
	csl.push_back(csl.front());
	csl.push_back(*std::next(csl.begin()));
	csl.push_back(*std::next(std::next(csl.begin())));
	list<jhm::vector> output;
	for(list< cs >::iterator csl_it = csl.begin(); csl_it != std::prev(std::prev(std::prev(csl.end()))); ++csl_it){
		cs cur_p_0 = *csl_it;
		cs cur_p_1 = *std::next(csl_it);
		cs cur_p_2 = *std::next(std::next(csl_it));
		cs cur_p_3 =*std::next(std::next(std::next(csl_it)));
		for(float t = 0.0; t <= 1.0; t = t + 1.0/N){
			cs point_at_t = drawBSplinepoint(t,cur_p_0,cur_p_1,cur_p_2,cur_p_3);
			jhm::vector temp = jhm::vector(point_at_t.first, 0, point_at_t.second);
			temp = rotate(quaternion,scalar * temp) + translation;
			output.push_back(temp);
		}
	}
	return output;
}
jhm::vector vector_bezier_point(double t,jhm::vector p_0, jhm::vector p_1, jhm::vector p_2, jhm::vector p_3){
	jhm::vector p_4 = interpolate(t,p_0,p_1);
	jhm::vector p_5 = interpolate(t,p_1,p_2);
	jhm::vector p_6 = interpolate(t,p_2,p_3);
	jhm::vector p_7 = interpolate(t,p_4,p_5);
	jhm::vector p_8 = interpolate(t,p_5,p_6);
	jhm::vector p_9 = interpolate(t,p_7,p_8);
	return p_9;
}
list<list<jhm::vector>> vector_interpolation (list<jhm::vector> vl){
	if(vl.size() < 2) {
		cout<< "Not enough length for vector interpolation"<<endl;
		exit(1);
	}
	jhm::vector p_0 = vl.front();
	jhm::vector p_1 = (*std::next(vl.begin()));
	jhm::vector p_end =vl.back();
	jhm::vector p_endm1 = (*std::prev(--vl.end()));
	jhm::vector p_m1 = p_0 - (p_1 - p_0);
	jhm::vector p_endp1 = p_end + (p_end - p_endm1);
	vl.push_front(p_m1);
	vl.push_back(p_endp1);
	list<list<jhm::vector>> output;
	for(list< jhm::vector >::iterator vl_it = std::next(vl.begin());vl_it != std::prev(vl.end()); ++vl_it){
		jhm::vector cur_p_0 = *vl_it;
		jhm::vector cur_p_1 = (*std::next(vl_it) - *std::prev(vl_it))* (1.0/6.0) + *vl_it;
		jhm::vector cur_p_2 = *std::next(vl_it) - (*std::next(std::next(vl_it)) - *vl_it)* (1.0/6.0);
		jhm::vector cur_p_3 = *std::next(vl_it);
		list<jhm::vector> interpolation;
		for(double t = 0.0; t < 1.0; t = t + 1.0/M){
			jhm::vector point_at_t = vector_bezier_point(t,cur_p_0,cur_p_1,cur_p_2,cur_p_3);
			interpolation.push_back(point_at_t);
		}
		output.push_back(interpolation);
	}
	return output;
}

jhm::quater quater_bezier_point (m_real t, jhm::quater q_0, jhm::quater q_1, jhm::quater q_2, jhm::quater q_3){
	jhm::quater q_4 = interpolate(t,q_0, q_1);
	jhm::quater q_5 = interpolate(t,q_1, q_2);
	jhm::quater q_6 = interpolate(t,q_2, q_3);
	jhm::quater q_7 = interpolate(t,q_4, q_5);
	jhm::quater q_8 = interpolate(t,q_5, q_6);
	jhm::quater q_9 = interpolate(t,q_7, q_8);
	return q_9;
}
list<list<jhm::quater>> quater_interpolation(list<jhm::quater> ql){
	if(ql.size() < 2) {
		cout<< "Not enough length for scalar interpolation"<<endl;
		exit(1);
	}
	jhm::quater q_0 = ql.front();
	jhm::quater q_1 = (*std::next(ql.begin()));
	jhm::quater q_end =ql.back();
	jhm::quater q_endm1 = (*std::prev(--ql.end()));
	jhm::quater q_m1 = q_0 - (q_1 - q_0);
	jhm::quater q_endp1 = q_end + (q_end - q_endm1);
	ql.push_front(q_m1);
	ql.push_back(q_endp1);
	list<list<jhm::quater>> output;
	for(list< jhm::quater >::iterator ql_it = std::next(ql.begin());ql_it != std::prev(ql.end()); ++ql_it){
		jhm::quater cur_q_0 = *ql_it;
		jhm::quater cur_q_1 = (*std::next(ql_it) - *std::prev(ql_it))* (1.0/6.0) + *ql_it;
		jhm::quater cur_q_2 = *std::next(ql_it) - (*std::next(std::next(ql_it)) - *ql_it)* (1.0/6.0);
		jhm::quater cur_q_3 = *std::next(ql_it);
		list<jhm::quater> interpolation;
		for(double t = 0.0; t < 1.0; t = t + 1.0/N){
			jhm::quater point_at_t = quater_bezier_point(t,cur_q_0,cur_q_1,cur_q_2,cur_q_3);
			interpolation.push_back(point_at_t);
		}
		output.push_back(interpolation);
	}
	return output;
	
}
m_real scalar_bezier_point(m_real t, m_real s_0, m_real s_1, m_real s_2, m_real s_3){
	m_real s_4 = (1.0 - t)* s_0 + t * s_1;
	m_real s_5 = (1.0 - t)* s_1 + t * s_2;
	m_real s_6 = (1.0 - t)* s_2 + t * s_3;
	m_real s_7 = (1.0 - t)* s_4 + t * s_5;
	m_real s_8 = (1.0 - t)* s_5 + t * s_6;
	m_real s_9 = (1.0 - t)* s_7 + t * s_8;
	return s_9;
}
list<list<m_real>> scalar_interpolation(list<m_real> sl){
	if(sl.size() < 2) {
		cout<< "Not enough length for scalar interpolation"<<endl;
		exit(1);
	}
	m_real s_0 = sl.front();
	m_real s_1 = (*std::next(sl.begin()));
	m_real s_end =sl.back();
	m_real s_endm1 = (*std::prev(--sl.end()));
	m_real s_m1 = s_0 - (s_1 - s_0);
	m_real s_endp1 = s_end + (s_end - s_endm1);
	sl.push_front(s_m1);
	sl.push_back(s_endp1);
	list<list<m_real>> output;
	for(list< m_real >::iterator sl_it = std::next(sl.begin());sl_it != std::prev(sl.end()); ++sl_it){
		m_real cur_s_0 = *sl_it;
		m_real cur_s_1 = (*std::next(sl_it) - *std::prev(sl_it))/6.0 + *sl_it;
		m_real cur_s_2 = *std::next(sl_it) - (*std::next(std::next(sl_it)) - *sl_it)/6.0;
		m_real cur_s_3 = *std::next(sl_it);
		list<m_real> interpolation;
		for(double t = 0.0; t < 1.0; t = t + 1.0/M){
			m_real point_at_t = scalar_bezier_point(t,cur_s_0,cur_s_1,cur_s_2,cur_s_3);
			interpolation.push_back(point_at_t);
		}
		output.push_back(interpolation);
	}
	return output;
	
}
tuple<list<m_real>,list<jhm::quater>,list<jhm::vector>> cst_translator (list<cst> input){
	list<m_real> output_s;
	list<jhm::quater> output_q;
	list<jhm::vector> output_v;
	for(list<cst>::iterator cstl_it = input.begin(); cstl_it!=input.end(); ++cstl_it){
		m_real scalar;
		tuple<float,tuple<float,float,float>> axis_angle;
		tuple<float,float,float> translation;
		tie(scalar,axis_angle,translation) = *cstl_it;
		output_s.push_back(scalar);
		m_real t_x,t_y,t_z;
		tie(t_x,t_y,t_z) = translation;
		output_v.push_back(jhm::vector(t_x,t_y,t_z));
		m_real q_x,q_y,q_z,theta;
		tie(q_x,q_y,q_z) = get<1>( axis_angle);
		theta = get<0> (axis_angle);
		output_q.push_back(jhm::quater(cos(theta/2), sin(theta/2) * q_x, sin(theta/2) * q_y, sin(theta/2) * q_z));
	}
	return make_tuple(output_s, output_q, output_v);
}
	Mesh::Mesh(){
		cout<<vertex_list.size() << endl;
		cout << face_list.size() << endl;	
	}
	void Mesh::insert_triangle(jhm::vector vertices[3],
	jhm::vector face_normal, material_type material,GLfloat opacity){
		int j = 0;
		int fv[3] = {-1,-1,-1};
		for( vector<vertex>::iterator i = vertex_list.begin() ; i!= vertex_list.end(); ++i){
			for(int k = 0; k< 3; k++){
				jhm::vector temp1 = (*i).position;
				jhm::vector temp2 = vertices[k];
				if(temp1[0] == temp2[0] && temp1[1] == temp2[1] && temp1[2] == temp2[2]){
					vertex_list[j].normal += face_normal;
					vertex_list[j].normal *= (1.0f / len(vertex_list[j].normal)); 
					fv[k] = j;	
				}
			}
			//cout << j << endl;
			j++;
		}
		for(int k = 0; k<3; k++){
			if(fv[k] == -1){
				fv[k] = vertex_list.size();
				vertex new_vertex = {vertices[k],face_normal* (1.0f/len(face_normal))};
				vertex_list.push_back(new_vertex);
			}
		}
		face new_face = {{fv[0],fv[1],fv[2]},face_normal,material,opacity};
		face_list.push_back(new_face);
	}
	void Mesh::drawMesh(void){
	glBegin(GL_TRIANGLES);
	for(vector<face>::iterator i = face_list.begin(); i != face_list.end(); ++i){
		setMaterial((*i).mt, (*i).opacity);
		vertex vertex1 = vertex_list[(*i).vertices[0]];
		vertex vertex2 = vertex_list[(*i).vertices[1]];
		vertex vertex3 = vertex_list[(*i).vertices[2]];
		glNormal3f(vertex1.normal[0],vertex1.normal[1],vertex1.normal[2]);
		glVertex3f(vertex1.position[0], vertex1.position[1], vertex1.position[2]);
		glNormal3f(vertex2.normal[0],vertex2.normal[1],vertex2.normal[2]);
		glVertex3f(vertex2.position[0], vertex2.position[1], vertex2.position[2]);
		glNormal3f(vertex3.normal[0],vertex3.normal[1],vertex3.normal[2]);
		glVertex3f(vertex3.position[0], vertex3.position[1], vertex3.position[2]);
	}
	glEnd();
	}


Mesh newMesh = Mesh();

void setMaterial(material_type mt,GLfloat opacity){
    
  if(mt == ruby){
    GLfloat ambient[4] = {0.17, 0.02, 0.02, opacity};
    GLfloat diffuse[4] = {0.6, 0.04, 0.04, opacity};
    GLfloat specular[4] = {0.78, 0.63, 0.63, opacity};
    GLfloat shininess = 0.6;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0 );
  }
  else if (mt == gold){
    GLfloat ambient[4] = {0.25, 0.2, 0.07, opacity};
    GLfloat diffuse[4] = {0.75, 0.60, 0.24, opacity};
    GLfloat specular[4] = {0.9, 0.9, 0.36, opacity};
    GLfloat shininess = 0.6;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0 );
  }
  else if (mt == silver){
    GLfloat ambient[4] = {0.22225, 0.22225, 0.22225, opacity};
    GLfloat diffuse[4] = {0.50754, 0.50754, 0.50754, opacity};
    GLfloat specular[4] = {0.508273, 0.508273, 0.508273, opacity};
    GLfloat shininess = 0.4;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0 );
  }
  else if (mt == bronze){
    GLfloat ambient[4] = {0.2125, 0.1275, 0.054, opacity};
    GLfloat diffuse[4] = {0.714, 0.4284, 0.18144, opacity};
    GLfloat specular[4] = {0.393548, 0.271906, 0.166721, opacity};
    GLfloat shininess = 0.2;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0 );
  }
  else if (mt == pearl){
    GLfloat ambient[4] = {0.24, 0.20725, 0.20725, opacity};
    GLfloat diffuse[4] = {0.94, 0.829, 0.829, opacity};
    GLfloat specular[4] = {0.296648, 0.296648, 0.296648, opacity};
    GLfloat shininess = 0.95;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0 );
  }
  else if (mt == jade){
    GLfloat ambient[4] = {0.0215, 0.1745, 0.2215, opacity};
    GLfloat diffuse[4] = {0.07568, 0.61424, 0.17568, opacity};
    GLfloat specular[4] = {0.633, 0.727811, 0.733, opacity};
    GLfloat shininess = 0.8;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0 );
  }
  else if (mt == plastic){
    GLfloat ambient[4] = {0.0, 0.0, 0.15, opacity};
    GLfloat diffuse[4] = {0.2, 0.3, 0.51, opacity};
    GLfloat specular[4] = {0.30, 0.30, 0.30, opacity};
    GLfloat shininess = 32.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess );
  }
  else{
  	return;
  }
}

void makeMesh(void){
	list<m_real> test_sl = get<0>(cst_translator(cross_section_transformations));
	list<list<m_real>> output = scalar_interpolation(test_sl);
	list<m_real> sl;
	list<jhm::quater> ql;
	list<jhm::vector> vl;
	tie(sl, ql, vl) = cst_translator(cross_section_transformations);
	list<list<m_real> > sl_intp = scalar_interpolation(sl);
	list<list<jhm::quater> > ql_intp = quater_interpolation(ql);
	list<list<jhm::vector> > vl_intp = vector_interpolation(vl);
	list<list<cs > >::iterator css_it = cross_sections.begin();
	list<list<m_real> >::iterator sl_outer_it = sl_intp.begin();
	list<list<jhm::quater> >::iterator ql_outer_it = ql_intp.begin();
	list<list<jhm::vector> >::iterator vl_outer_it = vl_intp.begin();
	list<list<jhm::vector> > mesh;
	int i = 0;
	for(;css_it != cross_sections.end(); ++css_it){
		list<m_real>::iterator sl_inner_it = (*sl_outer_it).begin();
		list<jhm::quater>::iterator ql_inner_it = (*ql_outer_it).begin();
		list<jhm::vector>::iterator vl_inner_it = (*vl_outer_it).begin();
		for(;sl_inner_it != (*sl_outer_it).end(); ++sl_inner_it){
			if(curvetype.compare("BSPLINE")==0)
				mesh.push_back(BSpline_vertices(*css_it, *sl_inner_it, *ql_inner_it, *vl_inner_it));
			else if(curvetype.compare("CATMULL_ROM")==0)
				mesh.push_back(CR_vertices(*css_it, *sl_inner_it, *ql_inner_it, *vl_inner_it));
			else{
				cout<<"Curve type not BSPLINE or CATMULL_ROM"<<endl;
				exit(1);
			}
			++ql_inner_it; ++vl_inner_it;
		}
		++sl_outer_it; ++ql_outer_it; ++vl_outer_it;
		
	}
	for(list<list<jhm::vector> >::iterator mesh_it_out = mesh.begin();mesh_it_out != std::prev(mesh.end()); ++mesh_it_out){
		list<jhm::vector>::iterator cur_cs = (*mesh_it_out).begin();
		list<jhm::vector>::iterator next_cs = (*std::next(mesh_it_out)).begin();
		jhm::vector prev_prev_vertex = *cur_cs;
		jhm::vector prev_vertex = *next_cs;
		++cur_cs; ++next_cs;
		for(;cur_cs != (*mesh_it_out).end();++cur_cs){
			jhm::unit_vector norm1 = -normalize((*cur_cs - prev_vertex)*(prev_vertex - prev_prev_vertex));
			jhm::unit_vector norm2 = -normalize((*cur_cs - prev_vertex)*(*next_cs - *cur_cs));
			jhm::vector triangle1[3] = {prev_prev_vertex, prev_vertex, *cur_cs};
			newMesh.insert_triangle(triangle1,norm1,plastic);
			jhm::vector triangle2[3] = {prev_vertex, *cur_cs,*next_cs};
			newMesh.insert_triangle(triangle2,norm2,plastic);
			prev_prev_vertex = *cur_cs;
			prev_vertex = *next_cs;
			++next_cs;
		}
		jhm::vector b2bu = (*mesh_it_out).front();
		jhm::vector b2bd = (*std::next(mesh_it_out)).front();
		jhm::unit_vector norm1 = -normalize((b2bu - prev_vertex)*(prev_vertex - prev_prev_vertex));
		jhm::unit_vector norm2 = -normalize((b2bu - prev_vertex)*(b2bd - b2bu));
		jhm::vector triangle1[3] = {prev_prev_vertex, prev_vertex, b2bu};
		newMesh.insert_triangle(triangle1,norm1,plastic);
		jhm::vector triangle2[3] = {prev_vertex, b2bu,b2bd};
		newMesh.insert_triangle(triangle2,norm2,plastic);
	}
}

void Quad2triangle(jhm::vector triangle1[3], jhm::vector triangle2[3], jhm::vector quad[4]){
	triangle1[0] = quad[0];
	triangle1[1] = quad[1];
	triangle1[2] = quad[2];
	triangle2[0] = quad[2];
	triangle2[1] = quad[3];
	triangle2[2] = quad[0];
}

void drawCube(material_type mt,GLfloat opacity){
	// top
	setMaterial(mt,opacity);
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glNormal3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glNormal3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glNormal3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
 
	// front
	glBegin(GL_QUADS);
	glNormal3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glNormal3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glNormal3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glNormal3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);

	// right
	glNormal3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glNormal3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glNormal3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glNormal3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	// left
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glNormal3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glNormal3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glNormal3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f); 
	glEnd();

	// bottom
	glBegin(GL_QUADS);
	glNormal3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glNormal3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glNormal3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glNormal3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f); 
	glEnd();
	
	//back
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glNormal3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glNormal3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glNormal3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
}
void drawCube_transparent(void){
	{
	jhm::vector v0(-0.5f, 0.5f, 0.5f);
	jhm::vector v1(0.5f, 0.5f, 0.5f);
	jhm::vector v2(0.5f, 0.5f, -0.5f);
	jhm::vector v3(-0.5f, 0.5f, -0.5f);
	jhm::vector quad[4] = {v0,v1,v2,v3};
	jhm::vector triangle1[3];
	jhm::vector triangle2[3];
	jhm::vector norm(0.0f,1.0f,0.0f);
	Quad2triangle(triangle1,triangle2,quad);
	newMesh.insert_triangle(triangle1, norm, ruby,0.8f);
	newMesh.insert_triangle(triangle2, norm, ruby,0.8f);
	}
	{
	jhm::vector v0(0.5f, -0.5f, 0.5f);
	jhm::vector v1(0.5f, 0.5f, 0.5f);
	jhm::vector v2(-0.5f, 0.5f, 0.5f);
	jhm::vector v3(-0.5f, -0.5f, 0.5f);
	jhm::vector quad[4] = {v0,v1,v2,v3};
	jhm::vector triangle1[3];
	jhm::vector triangle2[3];
	jhm::vector norm(0.0f,0.0f,1.0f);
	Quad2triangle(triangle1,triangle2,quad);
	newMesh.insert_triangle(triangle1, norm, gold,0.8f);
	newMesh.insert_triangle(triangle2, norm, gold,0.8f);
	}
	{
	jhm::vector v0(0.5f, 0.5f, -0.5f);
	jhm::vector v1(0.5f, 0.5f, 0.5f);
	jhm::vector v2(0.5f, -0.5f, 0.5f);
	jhm::vector v3(0.5f, -0.5f, -0.5f);
	jhm::vector quad[4] = {v0,v1,v2,v3};
	jhm::vector triangle1[3];
	jhm::vector triangle2[3];
	jhm::vector norm(1.0f,0.0f,0.0f);
	Quad2triangle(triangle1,triangle2,quad);
	newMesh.insert_triangle(triangle1, norm, silver, 0.8f);
	newMesh.insert_triangle(triangle2, norm, silver, 0.8f);
 	}
	{
	jhm::vector v0(-0.5f, -0.5f, 0.5f);
	jhm::vector v1(-0.5f, 0.5f, 0.5f);
	jhm::vector v2(-0.5f, 0.5f, -0.5f);
	jhm::vector v3(-0.5f, -0.5f, -0.5f);
	jhm::vector quad[4] = {v0,v1,v2,v3};
	jhm::vector triangle1[3];
	jhm::vector triangle2[3];
	jhm::vector norm(-1.0f,0.0f,0.0f);
	Quad2triangle(triangle1,triangle2,quad);
	newMesh.insert_triangle(triangle1, norm, bronze,0.8f);
	newMesh.insert_triangle(triangle2, norm, bronze,0.8f);
 	}
	{
	jhm::vector v0(0.5f, -0.5f, 0.5f);
	jhm::vector v1(-0.5f, -0.5f, 0.5f);
	jhm::vector v2(-0.5f, -0.5f, -0.5f);
	jhm::vector v3(0.5f, -0.5f, -0.5f);
	jhm::vector quad[4] = {v0,v1,v2,v3};
	jhm::vector triangle1[3];
	jhm::vector triangle2[3];
	jhm::vector norm(0.0f,-1.0f,0.0f);
	Quad2triangle(triangle1,triangle2,quad);
	newMesh.insert_triangle(triangle1, norm, pearl,0.8f);
	newMesh.insert_triangle(triangle2, norm, pearl,0.8f);
 	}
	{
	jhm::vector v0(0.5f, 0.5f, -0.5f);
	jhm::vector v1(0.5f, -0.5f, -0.5f);
	jhm::vector v2(-0.5f, -0.5f, -0.5f);
	jhm::vector v3(-0.5f, 0.5f, -0.5f);
	jhm::vector quad[4] = {v0,v1,v2,v3};
	jhm::vector triangle1[3];
	jhm::vector triangle2[3];
	jhm::vector norm(0.0f,0.0f,-1.0f);
	Quad2triangle(triangle1,triangle2,quad);
	newMesh.insert_triangle(triangle1, norm, jade,0.8f);
	newMesh.insert_triangle(triangle2, norm, jade,0.8f);
 	}
}


