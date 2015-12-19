#include "food.h"
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

float positionF[3] = {0.0,0.0,6.0};

void Food::drawFood(bool n)
{
	// generate random location of food if n==true
	if (n == true)
	{
	  int x = rand() % 8 * pow(-1,rand() % 3);
	  int y = rand() % 8 * pow(-1,rand() % 3);
    positionF[0] = (float) x;
    positionF[1] = (float) y;
  }
  
  glColor3f(1.0,1.0,0.0);    

  float vertices[4][3] = {
    {0,0,0},{4,0,0},{4,4,0},{0,4,0}
  };

  glPushMatrix();
   
  glTranslatef(positionF[0],positionF[1],positionF[2]);
  glScalef(0.07,0.07,0.07);

  glBegin(GL_POLYGON);
	for (int j = 0; j < 4; j++)
 	{
    glVertex3fv(vertices[j]);
  }
	glEnd();
	glPopMatrix();
}