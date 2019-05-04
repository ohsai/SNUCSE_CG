
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

float camera_lx = 0.0f, camera_lz = -1.0f;
float camera_ly = 0.0f;
float camera_x = 1.0f, camera_z = 2.0f;
float camera_y = 0.5f;
float camera_theta = 0.0f;
float deltatheta = 0.0f;
float camera_phi = 0.0f;
float deltaphi = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
int yOrigin = -1;


void drawReference(){
	glColor3f(1.0f,1.0f,1.0f);
	glutSolidSphere(0.1f,50,50);
	glBegin(GL_LINES);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f,0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f, 0.0f,0.0f);
	glVertex3f(0.0f,0.0f,1.0f);
	glEnd();
	glColor3f(1.0f,1.0f,1.0f);
}
void Cube(){
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(135,206,235);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(30,144,255);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(230,230,250);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(70,130,180);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(65,105,225);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(135,206,235);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}
void Cube_flesh(){
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(247,243,222);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(247,243,222);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(247,243,222);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(247,243,222);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(247,243,222);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(247,243,222);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}
void Cube_top(){
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(30,144,255);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(0,0,205);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(30,144,255);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(0,0,205);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(0,0,205);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(30,144,255);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}
void Cube_bottom2(){
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(178,34,34);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(128,0,0);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(178,34,34);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(128,0,0);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(128,0,0);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(178,34,34);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}
void Cube_bottom(){
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(0,0,50);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(0,0,30);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(0,0,50);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(0,0,30);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(0,0,30);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(0,0,50);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}

clock_t start;
float duration;
float location_x = 0.0f;
float location_y = 0.75f;
float location = -5.0f;
float location_initial = -5.0f;
float velocity = 20;

float BodyHeight = 0.5f;
float ThighHeight = 0.5 * BodyHeight;
float calfHeight = 0.5 * BodyHeight;
float footHeight = 0.6 * 0.5 * calfHeight;
float neck = 0.1 * BodyHeight;
float HeadHeight = 0.4 * BodyHeight;
float upperarm = 0.4 * BodyHeight;
float lowerarm = upperarm;
float hand = 0.6 * lowerarm;
void Body(){
	glScalef(BodyHeight/2.0f,BodyHeight,BodyHeight/2.0f);
	Cube();
}
void Calf(){
	glScalef(calfHeight/2.0f,calfHeight,calfHeight/2.0f);
	Cube_bottom2();
}
void Thigh(){
	glScalef(ThighHeight/2.0f,ThighHeight,ThighHeight/2.0f);
	Cube_bottom2();
}
void Foot(){
	glScalef(footHeight * 1.5,footHeight,footHeight* 3.0f);
	Cube_flesh();
}
void Neck(){
	glScalef(HeadHeight/2.0f,neck,HeadHeight/2.0f);
	glScalef(0.5f,0.5f,0.5f);
	Cube_flesh();
}
void Head(){
	glScalef(HeadHeight,HeadHeight,HeadHeight);
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(247,243,222);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(192,192,192);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}
void UpperArm(){
	glScalef(upperarm/2.0f, upperarm, upperarm/2.0f);
	Cube();
}
void LowerArm(){
	glScalef(lowerarm/2.0f, lowerarm, lowerarm/2.0f);
	Cube();
}
void Hand(){
	glScalef(hand, hand, hand);
	Cube_flesh();
}
void drawRunner(){
	glTranslatef(location_x,location_y,location);
	glRotatef(5,1.0f,0.0f,0.0f);
	glPushMatrix();
	Body();
		//right leg
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0,-BodyHeight/2.0f,0);
		glRotatef(-40 * sin(100*duration),1.0f, 0.0f,0.0f); 
		glTranslatef(-ThighHeight/2.0f,-(ThighHeight/2.0f), 0.0f);
		glPushMatrix();
		Thigh();
			glPopMatrix();
			glTranslatef(0,-ThighHeight/2.0f,0);
			glRotatef(45,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(calfHeight/2.0f), 0.0f);
			glPushMatrix();
			Calf();
				glPopMatrix();
				glTranslatef(0,-calfHeight/2.0f, 0);
				glRotatef(-30,1.0f,0.0f,0.0f);
				glTranslatef(0.0f, -(footHeight/2.0f),footHeight*1.5*0.5);
				Foot();
		//left leg
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0,-BodyHeight/2.0f,0);
		glRotatef(40 * sin(100*duration),1.0f, 0.0f,0.0f); 
		glTranslatef(ThighHeight/2.0f,-(ThighHeight/2.0f), 0.0f);
		glPushMatrix();
		Thigh();
			glPopMatrix();
			glTranslatef(0,-ThighHeight/2.0f,0);
			glRotatef(45,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(calfHeight/2.0f), 0.0f);
			glPushMatrix();
			Calf();
				glPopMatrix();
				glTranslatef(0,-calfHeight/2.0f, 0);
				glRotatef(-30,1.0f,0.0f,0.0f);
				glTranslatef(0.0f, -(footHeight/2.0f),footHeight*1.5*0.5);
				Foot();
		//left arm
		glPopMatrix();
		glPushMatrix();
		glTranslatef((BodyHeight/4.0f) ,(BodyHeight/2.0f), 0.0f);
		glRotatef(-40 * sin(100*duration),1.0f, 0.0f,0.0f); 
		glTranslatef(upperarm/4.0f,-upperarm/2.0f,0);
		glPushMatrix();
		UpperArm();
			glPopMatrix();
			glTranslatef(0,-upperarm/2.0f,0);
			glRotatef(-90,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(lowerarm/2.0f), 0.0f);
			glPushMatrix();
			LowerArm(); 
				glPopMatrix();
				glTranslatef(0,-lowerarm/2.0f,0);
				glTranslatef(0.0f, -(hand/2.0f),0.0f);
				Hand();
		//right arm		
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-(BodyHeight/4.0f) ,(BodyHeight/2.0f), 0.0f);
		glRotatef(40 * sin(100 * duration),1.0f, 0.0f,0.0f); 
		glTranslatef(- upperarm/4.0f,-upperarm/2.0f,0);
		glPushMatrix();
		UpperArm();
			glPopMatrix();
			glTranslatef(0,-upperarm/2.0f,0);
			glRotatef(-90 ,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(lowerarm/2.0f), 0.0f);
			glPushMatrix();
			LowerArm(); 
				glPopMatrix();
				glTranslatef(0,-lowerarm/2.0f,0);
				glTranslatef(0.0f, -(hand/2.0f),0.0f);
				Hand();
		//head
		glPopMatrix();
		glTranslatef(0,BodyHeight/2.0f,0);
		glTranslatef(0.0f, neck/2.0f,0.0f);
		glPushMatrix();
		Neck();
			glPopMatrix();
			glTranslatef(0,neck/2.0f,0);
			glTranslatef(0.0f, HeadHeight/2.0f, 0.0f);
			Head();
}
void Body_p(){
	glScalef(BodyHeight/2.0f,BodyHeight,BodyHeight/2.0f);
	Cube_top();
}
void Calf_p(){
	glScalef(calfHeight/2.0f,calfHeight,calfHeight/2.0f);
	Cube_bottom();
}
void Thigh_p(){
	glScalef(ThighHeight/2.0f,ThighHeight,ThighHeight/2.0f);
	Cube_bottom();
}
void Foot_p(){
	glScalef(footHeight * 1.5,footHeight,footHeight* 3.0f);
	Cube_flesh();
}
void Neck_p(){
	glScalef(HeadHeight/2.0f,neck,HeadHeight/2.0f);
	glScalef(0.5f,0.5f,0.5f);
	Cube_flesh();
}
void Head_p(){
	glScalef(HeadHeight,HeadHeight,HeadHeight);
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(247,243,222);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(192,192,192);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(192,192,192);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}
void UpperArm_p(){
	glScalef(upperarm/2.0f, upperarm, upperarm/2.0f);
	Cube_top();
}
void LowerArm_p(){
	glScalef(lowerarm/2.0f, lowerarm, lowerarm/2.0f);
	Cube_top();
}
void Hand_p(){
	glScalef(hand, hand, hand);
	Cube_flesh();
}
void Cube_Rod(){
	glScalef(0.5f,0.5f,0.5f);
	glBegin(GL_QUADS);
	glColor3ub(128,128,128);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glColor3ub(105,105,105);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glColor3ub(128,128,128);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glColor3ub(105,105,105);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glColor3ub(105,105,105);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glColor3ub(128,128,128);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glEnd();
}
float rod = hand * 2/3;
void Rod_p(){
	glScalef(rod, rod, rod * 4);
	Cube_Rod();
}
void drawPolice(){
	glTranslatef(location_x,location_y,location - 3.0f);
	glRotatef(5,1.0f,0.0f,0.0f);
	glPushMatrix();
	Body_p();
		//right leg
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0,-BodyHeight/2.0f,0);
		glRotatef(-40 * sin(100*duration),1.0f, 0.0f,0.0f); 
		glTranslatef(-ThighHeight/2.0f,-(ThighHeight/2.0f), 0.0f);
		glPushMatrix();
		Thigh_p();
			glPopMatrix();
			glTranslatef(0,-ThighHeight/2.0f,0);
			glRotatef(45,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(calfHeight/2.0f), 0.0f);
			glPushMatrix();
			Calf_p();
				glPopMatrix();
				glTranslatef(0,-calfHeight/2.0f, 0);
				glRotatef(-30,1.0f,0.0f,0.0f);
				glTranslatef(0.0f, -(footHeight/2.0f),footHeight*1.5*0.5);
				Foot_p();
		//left leg
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0,-BodyHeight/2.0f,0);
		glRotatef(40 * sin(100*duration),1.0f, 0.0f,0.0f); 
		glTranslatef(ThighHeight/2.0f,-(ThighHeight/2.0f), 0.0f);
		glPushMatrix();
		Thigh_p();
			glPopMatrix();
			glTranslatef(0,-ThighHeight/2.0f,0);
			glRotatef(45,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(calfHeight/2.0f), 0.0f);
			glPushMatrix();
			Calf_p();
				glPopMatrix();
				glTranslatef(0,-calfHeight/2.0f, 0);
				glRotatef(-30,1.0f,0.0f,0.0f);
				glTranslatef(0.0f, -(footHeight/2.0f),footHeight*1.5*0.5);
				Foot_p();
		//left arm
		glPopMatrix();
		glPushMatrix();
		glTranslatef((BodyHeight/4.0f) ,(BodyHeight/2.0f), 0.0f);
		glRotatef(-40 * sin(100*duration),1.0f, 0.0f,0.0f); 
		glTranslatef(upperarm/4.0f,-upperarm/2.0f,0);
		glPushMatrix();
		UpperArm_p();
			glPopMatrix();
			glTranslatef(0,-upperarm/2.0f,0);
			glRotatef(-90,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(lowerarm/2.0f), 0.0f);
			glPushMatrix();
			LowerArm_p(); 
				glPopMatrix();
				glTranslatef(0,-lowerarm/2.0f,0);
				glTranslatef(0.0f, -(hand/2.0f),0.0f);
				glPushMatrix();	
				Hand_p();
					glPopMatrix();
					glTranslatef(0,0,hand/2.0f);
					glTranslatef(0,0,rod * 2.0f);
					Rod_p();
				
		//right arm		
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-(BodyHeight/4.0f) ,(BodyHeight/2.0f), 0.0f);
		glRotatef(40 * sin(100 * duration),1.0f, 0.0f,0.0f); 
		glTranslatef(- upperarm/4.0f,-upperarm/2.0f,0);
		glPushMatrix();
		UpperArm_p();
			glPopMatrix();
			glTranslatef(0,-upperarm/2.0f,0);
			glRotatef(-90 ,1.0f,0.0f,0.0f);
			glTranslatef(0.0f, -(lowerarm/2.0f), 0.0f);
			glPushMatrix();
			LowerArm_p(); 
				glPopMatrix();
				glTranslatef(0,-lowerarm/2.0f,0);
				glTranslatef(0.0f, -(hand/2.0f),0.0f);
				Hand_p();
		//head
		glPopMatrix();
		glTranslatef(0,BodyHeight/2.0f,0);
		glTranslatef(0.0f, neck/2.0f,0.0f);
		glPushMatrix();
		Neck_p();
			glPopMatrix();
			glTranslatef(0,neck/2.0f,0);
			glTranslatef(0.0f, HeadHeight/2.0f, 0.0f);
			Head_p();
}

bool valueUpdated(int & current, int & previous){
	if(current !=previous){
		previous = current;
		return true;
	}
	else{
		return false;
	}
}

int phase = 0;
int phase_previous = 0;

void cameraWork(){
	duration = 2 * (clock() - start ) / (float) CLOCKS_PER_SEC;
	location = velocity * duration + location_initial;
	phase = ((int)(duration * 10)) % 3;
	if(valueUpdated(phase, phase_previous)){
		if(phase == 0){
			camera_x = 3.0f;
			camera_y = 0.75f;
			camera_z = location + 2.0f;
		}
		else if(phase == 1){
			camera_x = 0.25f;
			camera_y = 1.0f;
			camera_z = location + 5.0f;
		}
		else{
			camera_x = -3.0f;
			camera_y = 5.0f;
			camera_z = location + 1.0f;
		}
	}
	
	float deltax = location_x - camera_x;
	float deltay = location_y - camera_y;
	float deltaz = location - camera_z;
	camera_theta = M_PI - atan2(deltax, deltaz); 
	camera_phi = atan2(deltay, sqrt(deltax * deltax + deltaz * deltaz));
	camera_lx = cos(camera_phi + deltaphi) *
		sin(camera_theta + deltatheta);
	camera_ly = sin(camera_phi + deltaphi);
	camera_lz = cos(camera_phi + deltaphi) * 
		-cos(camera_theta + deltatheta);
}

void drawScene(){
	cameraWork();	       	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x,camera_y,camera_z, 
		camera_x+camera_lx, camera_y + camera_ly, camera_z+camera_lz,
	       0.0f, 1.0f, 0.0f);
	//drawReference();
	glPushMatrix();
	drawRunner();
	glPopMatrix();
	drawPolice();
	glutSwapBuffers();
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON){
		if(state == GLUT_UP){
			camera_theta += deltatheta;
			camera_phi += deltaphi;
			xOrigin = -1;
			yOrigin = -1;
		}
		else{
			xOrigin = x;
			yOrigin = y;
		}
	}
}
void mouseMove(int x, int y){
	if (xOrigin >= 0){
		deltatheta = (x- xOrigin) * 0.002f;
		deltaphi = -(y- yOrigin) * 0.002f;
	}
}

void handleResize(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,
			(double)w/(double)h,
			1.0,
			200.0);
}

void handleKeypress(unsigned char key, int x, int y){
	switch(key){
		case 27: exit(0);	
	}
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
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(50,0);
    glutCreateWindow("Example");
    InitRendering();

    glutTimerFunc(timeStep,Timer,0);
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    //glutIdleFunc(drawScene);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    glutMainLoop();
    return 0;
}

