#include "walls.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include<ctype.h>
#include<math.h>
#include<stdio.h>


const int WALLS_X = 31;
const int WALLS_Y = 28;

int Walls_array[WALLS_X][WALLS_Y] =
  { 
	{ 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 7, 0, 8, 1, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 1, 7, 0, 8, 1, 1, 7, 0, 6 },
	{ 6, 0, 2, 11, 11, 4, 0, 2, 11, 11, 11, 4, 0, 2, 4, 0, 2, 11, 11, 11, 4, 0, 2, 11, 11, 4, 0, 6 },
	{ 6, 0, 9, 3, 3, 10, 0, 9, 3, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 3, 10, 0, 9, 3, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 7, 0, 8, 7, 0, 8, 1, 1, 1, 1, 1, 1, 7, 0, 8, 7, 0, 8, 1, 1, 7, 0, 6 },
	{ 6, 0, 9, 3, 3, 10, 0, 2, 4, 0, 9, 3, 3, 11, 11, 3, 3, 10, 0, 2, 4, 0, 9, 3, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 6 },
	{ 9, 5, 5, 5, 5, 7, 0, 2, 11, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 11, 4, 0, 8, 5, 5, 5, 5, 10 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 11, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 11, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 8, 5, 5, 1, 1, 5, 5, 7, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 5, 5, 5, 5, 5, 10, 0, 9, 10, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 9, 10, 0, 9, 5, 5, 5, 5, 5 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 5, 5, 5, 5, 7, 0, 8, 7, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 8, 7, 0, 8, 5, 5, 5, 5, 5 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 9, 5, 5, 5, 5, 5, 5, 10, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 8, 1, 1, 1, 1, 1, 1, 7, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 8, 5, 5, 5, 5, 10, 0, 9, 10, 0, 9, 3, 3, 11, 11, 3, 3, 10, 0, 9, 10, 0, 9, 5, 5, 5, 5, 7 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 7, 0, 8, 1, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 1, 7, 0, 8, 1, 1, 7, 0, 6 },
	{ 6, 0, 9, 3, 11, 4, 0, 9, 3, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 3, 10, 0, 2, 11, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 6 },
	{ 2, 1, 7, 0, 2, 4, 0, 8, 7, 0, 8, 1, 1, 1, 1, 1, 1, 7, 0, 8, 7, 0, 2, 4, 0, 8, 1, 4 },
	{ 2, 3, 10, 0, 9, 10, 0, 2, 4, 0, 9, 3, 3, 11, 11, 3, 3, 10, 0, 2, 4, 0, 9, 10, 0, 9, 3, 4 },
	{ 6, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 1, 1, 11, 11, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 11, 11, 1, 1, 1, 1, 7, 0, 6 },
	{ 6, 0, 9, 3, 3, 3, 3, 3, 3, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 3, 3, 3, 3, 3, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10 }
	};

GLubyte list[5];

void Walls::drawWalls (void)
{
	glColor3f(0, 0, 1);

	for (int I = 0; I < WALLS_X; I++)
	{
		for (int j = 0; j < WALLS_Y / 2; j++)
		{
			glColor3f(0, 0, 1);
			int call_this = 0;

			glPushMatrix();
			glTranslatef(-(float)WALLS_X / 2.0f, -(float)WALLS_Y / 2.0f, 0);

			glTranslatef(j, WALLS_Y - I, 0);

			glPushMatrix();
			glTranslatef(0.5, 0.5, 0);

			switch (Walls_array[I][j])
			{
				case 4:
					glRotatef(90.0, 0, 0, 1);
				case 3:
					glRotatef(90.0, 0, 0, 1);
				case 2:
					glRotatef(90.0, 0, 0, 1);
				case 1:
					call_this = 1;
					break;
				case 6:
					glRotatef(90.0, 0, 0, 1);
				case 5:
					call_this = 2;
					break;
				case 10:
					glRotatef(90.0, 0, 0, 1);
				case 9:
					glRotatef(90.0, 0, 0, 1);
				case 8:
					glRotatef(90.0, 0, 0, 1);
				case 7:
					call_this = 3;
					break;
			}

			glScalef(1, 1, 0.5);
			glTranslatef(-0.5, -0.5, 0);
			glCallList(list[call_this]);
			glPopMatrix();

			if (call_this != 0 || Walls_array[I][j] == 11)
			{
				glTranslatef(0, 0, -0.5);
				glCallList(list[4]);
			}
			glPopMatrix();
		}
	}

	int I;

	for (I = 0; I< WALLS_X; I++)
	{
		for (int j = WALLS_Y - 1; j >= WALLS_Y / 2; j--)
		{
			glColor3f(0, 0, 1);
			int call_this = 0;

			glPushMatrix();

			glTranslatef(-(float)WALLS_X / 2.0f, -(float)WALLS_Y / 2.0f, 0);
			glTranslatef(j, WALLS_Y - I, 0);

			glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			switch (Walls_array[I][j])
			{
			case 4:
				glRotatef(90.0, 0, 0, 1);
			case 3:
				glRotatef(90.0, 0, 0, 1);
			case 2:
				glRotatef(90.0, 0, 0, 1);
			case 1:
				call_this = 1;
				break;
			case 6:
				glRotatef(90.0, 0, 0, 1);
			case 5:
				call_this = 2;
				break;
			case 10:
				glRotatef(90.0, 0, 0, 1);
			case 9:
				glRotatef(90.0, 0, 0, 1);
			case 8:
				glRotatef(90.0, 0, 0, 1);
			case 7:
				call_this = 3;
				break;
			}
			glScalef(1, 1, 0.5);
			glTranslatef(-0.5, -0.5, 0);
			glCallList(list[call_this]);
			glPopMatrix();

			if (call_this != 0 || Walls_array[I][j] == 11)
			{
				glTranslatef(0, 0, -0.5);
				glCallList(list[4]);
			}
			glPopMatrix();
		}
	}
}

void Walls::createList()
{
	list[1] = glGenLists(1);

	glNewList(list[1], GL_COMPILE);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 1.0);
	glEnd();

	glEndList();

	list[2] = glGenLists(1);
	glNewList(list[2], GL_COMPILE);

	glBegin(GL_QUADS);

	glColor3f(0, 0, 1);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 1.0);

	glColor3f(0, 0, 1);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glEndList();

	list[3] = glGenLists(1);

	glNewList(list[3], GL_COMPILE);
	glBegin(GL_QUADS);

	glColor3f(0, 0, 1);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 1.0);

	glColor3f(0, 0, 1);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glEndList();

	list[4] = glGenLists(1);

	glNewList(list[4], GL_COMPILE);
	glBegin(GL_QUADS);

	glColor3f(0, 0, 1);
	glNormal3f(1.0, 0.0, 1.0);
	glVertex3f(1, 1, 1.0);
	glVertex3f(0, 1, 1.0);
	glVertex3f(0, 0, 1.0);
	glVertex3f(1, 0, 1.0);
	glEnd();
	glEndList();
}

