/*
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include <list>
#include <tuple>
using namespace std;


typedef pair<float,float> cs;
list< cs > cross_sections;

typedef tuple<  float, tuple<float, tuple<float,float,float> >,tuple<float,float,float> > cst; 
list< cst > cross_section_transformations;

string curvetype;
int cross_section_number, control_points_number;

*/
#include "parse.h"

list<list< cs > > cross_sections;
list< cst > cross_section_transformations;
string curvetype;
int cross_section_number, control_points_number;

void input_reader(int argc, char* argv[]){
 if(argc != 2) {
 	cout << "Give one and only one argument to the program : path to datafile (.txt)"<<endl;
	exit(1);
 }
 ifstream datafile(argv[1]);
 datafile >> curvetype;
 datafile >> cross_section_number >> control_points_number;
 for( int i = 0; i < cross_section_number ; i++){
  list< cs > cross_section;
  for(int j = 0; j < control_points_number; j++){
   string xtemp, ytemp;
   datafile >> xtemp >> ytemp;
   //cout << xtemp << " " << ytemp << endl;
   cs cs_temp = make_pair(atof(xtemp.c_str()), atof(ytemp.c_str()));
   cross_section.push_back(cs_temp);
  }
  cross_sections.push_back(cross_section);
  string scale_factor;
  string axis_angle, axis_x, axis_y, axis_z;
  string trans_x, trans_y, trans_z;
  datafile >> scale_factor >> axis_angle >> axis_x >> axis_y >> axis_z;
  datafile >> trans_x >> trans_y >> trans_z;
  cst cst_temp = make_tuple(atof(scale_factor.c_str()),make_tuple(atof(axis_angle.c_str()),make_tuple(atof(axis_x.c_str()), atof(axis_y.c_str()), atof(axis_z.c_str()))),make_tuple(atof(trans_x.c_str()),atof(trans_y.c_str()),atof(trans_z.c_str())));
  cross_section_transformations.push_back(cst_temp);
  //cout << atof(scale_factor.c_str()) <<" "<< axis_angle <<" " <<  trans_x << endl;
 }
}
/*
int main()
{
 input_reader();
 list<cst>::iterator it = cross_section_transformations.begin();
 it = next(it);
 cout<< std::get<0>(*it) << endl;
}
*/
