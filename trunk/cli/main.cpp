
/**
 * OpenEmulator
 * CLI Main
 * (C) 2009-2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Program entry point.
 */

#include "stdio.h"
#include "math.h"

#ifdef __APPLE__
#include "GLUT/glut.h"
#else
#include "GL/glut.h"
#endif

#include "OEPortaudio.h"

GLfloat light0_ambient[] =	{0.2, 0.2, 0.2, 1.0};
GLfloat light0_diffuse[] =	{0.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] =	{1.0, 0.0, 0.0, 1.0};
GLfloat light1_position[] =	{1.0, 1.0, 1.0, 0.0};
GLfloat light2_diffuse[] =	{0.0, 1.0, 0.0, 1.0};
GLfloat light2_position[] =	{-1.0, -1.0, 1.0, 0.0};
GLfloat angle1 = 0.0;
GLfloat angle2 = 0.0;

void initAnimation()
{
	glNewList(1, GL_COMPILE);
	glutSolidIcosahedron();
	glEndList();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(0.5);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
				   /* aspect ratio */ 1.0,
				   /* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
			  0.0, 0.0, 0.0,      /* center is at (0,0,0) */
			  0.0, 1.0, 0.);      /* up is in positive Y direction */
	glTranslatef(0.0, 0.6, -1.0);
	
}

void updateAnimation()
{
	angle1 = (GLfloat) fmod(angle1 + 360.0/200, 360.0);
	glutPostRedisplay();
}

void drawAnimation()
{
	static GLfloat amb[] = {0.4, 0.4, 0.4, 0.0};
	static GLfloat dif[] = {1.0, 1.0, 1.0, 0.0};
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	amb[3] = dif[3] = 2.5;
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	
	glPushMatrix();
	glRotatef(angle1, 1.0, 5.0, 0.0);
	glCallList(1);
	glPopMatrix();
}

void displayFunc(void)
{
	drawAnimation();
	
	glutSwapBuffers();
}

void reshapeFunc(int width, int height)
{
	
}

void keyboardFunc(unsigned char key, int x, int y)
{
	// Send ioctl with ASCII key
}

void mouseFunc(int button, int state, int x, int y)
{
	// button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
	// StatE: GLUT_UP or GLUT_DOWN
	// Send ioctl
}

void visibilityFunc(int value)
{
	// value: GLUT_VISIBLE or GLUT_NOT_VISIBLE
}

void specialFunc(int key, int x, int y)
{
	// Send ioctl with special key
	switch (key)
	{
		case GLUT_KEY_F1:
		case GLUT_KEY_F2:
		case GLUT_KEY_F3:
		case GLUT_KEY_F4:
		case GLUT_KEY_F5:
		case GLUT_KEY_F6:
		case GLUT_KEY_F7:
		case GLUT_KEY_F8:
		case GLUT_KEY_F9:
		case GLUT_KEY_F10:
		case GLUT_KEY_F11:
		case GLUT_KEY_F12:
		case GLUT_KEY_LEFT:
		case GLUT_KEY_UP:
		case GLUT_KEY_RIGHT:
		case GLUT_KEY_DOWN:
		case GLUT_KEY_PAGE_UP:
		case GLUT_KEY_PAGE_DOWN:
		case GLUT_KEY_HOME:
		case GLUT_KEY_END:
		case GLUT_KEY_INSERT:
			break;
	}
}

void timerFunc(int value)
{
	updateAnimation();
	glutTimerFunc(20, timerFunc, 0);
}

int main(int argc, char *argv[])
{
	oepaOpen();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("OpenEmulator");
	glutReshapeWindow(640, 480);
	
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutMouseFunc(mouseFunc);
	glutVisibilityFunc(visibilityFunc);
	glutSpecialFunc(specialFunc);
	glutTimerFunc(0, timerFunc, 0);
	
	initAnimation();
	
	glutMainLoop();
	
	oepaClose();
	return 0;
}
