/*
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

using namespace std;
*/ 
#include "model.h"
#include "trackball.h"
#include "parse.h"
//modeldone

clock_t start;
float duration;

void drawScene(){
	duration =  (clock() - start ) / (float) CLOCKS_PER_SEC;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x,camera_y,camera_z, 
		lookat_x, lookat_y, lookat_z,
	       up_x, up_y, up_z);
	//drawReference();
	//drawBSpline(cross_sections.back());
	//drawBSpline(cross_sections.back(),0.5,jhm::quater(cos(30.0 * M_PI/180.0),0,0,sin(30 * M_PI / 180.0) * 1),jhm::vector(0,0,0));
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	drawMesh();
	glutSwapBuffers();
}
void handleResize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective_aspect = (double)w / (double)h;
	gluPerspective(perspective_fov,
			perspective_aspect,
			perspective_znear,
			perspective_zfar);
}
void InitRendering(){
    glEnable(GL_DEPTH_TEST);
}

unsigned timeStep = 10;
void Timer(int unused){
	glutPostRedisplay();
	glutTimerFunc(timeStep, Timer, 0);
}

int main(int argc, char** argv){
	
    start = clock();

    input_reader(argc, argv);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(50,0);
    glutCreateWindow("HomeWork3");
    InitRendering();

    glutTimerFunc(timeStep,Timer,0);
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutSpecialFunc(handleArrowPress);	
    glutMainLoop();
    return 0;
}

