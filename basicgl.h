#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctime>
#include <cstdio>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <list>
#include <tuple>
#include <vector>
#include "mathclass.h"
using namespace std;
typedef pair<float,float> cs;
extern list<list< cs >> cross_sections;

typedef tuple<  float, tuple<float, tuple<float,float,float> >,tuple<float,float,float> > cst; 
extern list< cst > cross_section_transformations;

extern string curvetype;
extern int cross_section_number, control_points_number;


