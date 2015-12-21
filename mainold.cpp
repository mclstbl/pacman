#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
//#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "pacman.h"
#include "ghost.h"
#include "food.h"
#include "walls.h"

float verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };

float pos[] = {0,1,0};
float rot[] = {0, 0, 0};
float headRot[] = {0, 0, 0};
// this one works to view multiple cube faces
//float camPos[] = {10, 10, 20};
// flat view
float camPos[] = {0, 0, 20};

float angle = 0.0f;

Walls W1;
Pacman P1;
Ghost chaser = Ghost(0);
Ghost ambusher = Ghost(1);
Ghost fickle = Ghost(2);
Ghost ignorance = Ghost(3);
Food food1;
bool newFood = true;

void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}

void cube(float v[8][3])
{
	glColor3fv(cols[1]);
	drawPolygon(0, 3, 2, 1, v);

	glColor3fv(cols[2]);
	drawPolygon(1, 0, 4, 5, v);

	glColor3fv(cols[3]);
	drawPolygon(5, 1, 2, 6, v);
	
	glColor3fv(cols[4]);
	drawPolygon(2, 3, 7, 6, v);
	
	glColor3fv(cols[5]);
	drawPolygon(6, 5, 4, 7, v);

	glColor3fv(cols[0]);
	drawPolygon(4, 0, 3, 7, v);
}

void drawBox(float* c, float w, float h, float d)
{
	float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]+d/2}, 
							 {c[0]-w/2, c[1]-h/2, c[2]-d/2}, 
							 {c[0]-w/2, c[1]+h/2, c[2]-d/2}, 
							 {c[0]+w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]-d/2} };

	cube(vertices);
}


void keyboard(unsigned char key, int x, int y)
{

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;

		case 'a':
		case 'A':
			if(pos[0] > -4.4)
				pos[0] -= 0.1;
			rot[1] = -90;
			break;

		case 'w':
		case 'W':
			if(pos[2] > -4.4)
				pos[2] -= 0.1;
			rot[1] = 180;
			break;

		case 'd':
		case 'D':
			if(pos[0] < 4.4)
				pos[0]+=0.1;
			rot[1] = 90;
			break;

		case 's':
		case 'S':
			if(pos[2] < 4.4)
				pos[2] += 0.1;
			rot[1] = 0;
			break;

		case 'y':
		case 'Y':
			if(headRot[1] < 85)
				headRot[1] += 1;
			break;

		case 'u':
		case 'U':
			if(headRot[1] > -85)
				headRot[1] -= 1;
			break;
			
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			//camPos[0]-=0.1;
		  P1.changeDirection(0);
			break;

		case GLUT_KEY_RIGHT:
			//camPos[0]+=0.1;
		  P1.changeDirection(1);
			break;

		case GLUT_KEY_UP:
			//camPos[2] -= 0.1;
		  P1.changeDirection(2);
			break;

		case GLUT_KEY_DOWN:
			//camPos[2] += 0.1;
		  P1.changeDirection(3);
			break;
		
		case GLUT_KEY_HOME:
			camPos[1] += 0.1;
			break;

		case GLUT_KEY_END:
			camPos[1] -= 0.1;
			break;
	}
	glutPostRedisplay();
}

void init(void)
{    
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2, 2, -2, 2, -2, 2);
	gluPerspective(45, 1, 1, 100);

	glEnable(GL_DEPTH_TEST);
}

void idle(void)
{
  P1.move();
  //chaser.move();
  //ambusher.move();
  //fickle.move();
  //ignorance.move();

  glutPostRedisplay();
}

void display(void)
{
	float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glColor3f(1,1,1);

	//drawBox(origin, 10, 10, 10);
	

	glScalef(0.5, 0.5, 0.5);
	W1.drawWalls();
  P1.drawPacman(1);
	
	chaser.drawGhost(1);
  ambusher.drawGhost(1);
	fickle.drawGhost(1);
	ignorance.drawGhost(1);

  if (newFood)
  {
  	food1.drawFood(true,1);
  }
  else
  {
  	food1.drawFood(false,1);
  }

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(2200, 1600);
	glutInitWindowPosition(800, 0);

	glutCreateWindow("Pacman");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	init();

	W1.createList();

	glutMainLoop();

	return(0);
}