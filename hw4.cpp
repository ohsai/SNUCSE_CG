#include "model.h"
#include "trackball.h"
#include "parse.h"
#include "bsp.h"

BSPtree* bsptreep;

void drawScene(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x,camera_y,camera_z, 
		lookat_x, lookat_y, lookat_z,
	       up_x, up_y, up_z);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(1.5f,-1.0f,0.0f);
	drawCube(silver,1.0f);
	glTranslatef(0.0f,0.0f,1.5f);
	drawCube(bronze,1.0f);
	glTranslatef(-1.5f,0.0f,0.0f);
	drawCube(pearl,1.0f);
	glTranslatef(-1.5f,0.0f,0.0f);
	drawCube(jade,1.0f);
	glTranslatef(0.0f,0.0f,1.5f);
	drawCube(gold,1.0f);
	glTranslatef(1.5f,0.0f,0.0f);
	drawCube(ruby,1.0f);
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    	glEnable(GL_BLEND);
	jhm::vector cur_eye = jhm::vector(camera_x,camera_y,camera_z);
	bsptreep->render(cur_eye);	
    	glDisable(GL_BLEND);
	glutSwapBuffers();
	glutPostRedisplay();
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
unsigned timeStep = 10;

void Timer(int unused){
	glutTimerFunc(timeStep, Timer, 0);
}
void InitWindow(){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(50,0);
    glutCreateWindow("HomeWork4");
    glutTimerFunc(timeStep,Timer,0);
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutSpecialFunc(handleArrowPress);	
}
void InitRendering(){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_LIGHTING);
    //glEnable(GL_DEPTH_TEST);
    {GLfloat AmbientLightValue[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat DiffuseLightValue[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat SpecularLightValue[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat PositionLightValue[] = { 0.0f, 0.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT,AmbientLightValue);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,DiffuseLightValue);
    glLightfv(GL_LIGHT0, GL_SPECULAR,SpecularLightValue);
    glLightfv(GL_LIGHT0, GL_POSITION,PositionLightValue);}
    {GLfloat AmbientLightValue[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat DiffuseLightValue[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat SpecularLightValue[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat PositionLightValue[] = { 10.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT,AmbientLightValue);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,DiffuseLightValue);
    glLightfv(GL_LIGHT1, GL_SPECULAR,SpecularLightValue);
    glLightfv(GL_LIGHT1, GL_POSITION,PositionLightValue);}
    {GLfloat AmbientLightValue[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat DiffuseLightValue[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat SpecularLightValue[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat PositionLightValue[] = { 0.0f, 10.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT2, GL_AMBIENT,AmbientLightValue);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,DiffuseLightValue);
    glLightfv(GL_LIGHT2, GL_SPECULAR,SpecularLightValue);
    glLightfv(GL_LIGHT2, GL_POSITION,PositionLightValue);}
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
}
void makeScene(){
    cout<< "Constructing Mesh.. " <<endl;
    drawCube_transparent();
    makeMesh();
    cout << "Constructing BSPTree.."<<endl;
    bsptreep = new BSPtree(newMesh);
    //bsptreep->render(jhm::vector(3.0f,0.0f,0.0f));
}


int main(int argc, char** argv){
    input_reader(argc, argv);
    glutInit(&argc, argv);
    InitWindow();
    InitRendering();
    makeScene();
    glutMainLoop();
    delete bsptreep;
    return 0;
}

