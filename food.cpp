#include "food.h"	//including the food header
#include <stdlib.h>	//including standard library
#include <math.h>	//including math functions

//includes for APPLE
//including GLUT
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>

float positionF[3] = {0.0,0.0,6.0}; //setting position of the food

void Food::drawFood(bool n,int shine){	//drawFood function of object Food
	// generate new random location of food if n==true
	if (n == true){
	  int x = rand() % 5 * pow(-1,rand() % 2);	//creating a random x position
	  int y = rand() % 5 * pow(-1,rand() % 2);	//creating a random y position
    positionF[0] = (float) x;	//applying x position
    positionF[1] = (float) y;	//applying y position
  }
  
  glColor3f(1.0,1.0,0.0);    //changing color to yellow

  //vertices float array which define the square
  float vertices[4][3] = {
    {0,0,0},{4,0,0},{4,4,0},{0,4,0}
  };

  float specs[2][4][3] = {
    {{0,0,8},{0.5,0,8},{0.5,0.5,8},{0,0.5,8}},
    {{0,0,8},{0.7,0,8},{0.7,0.7,8},{0,0.7,8}},
  };

  glPushMatrix();	//save current matrix
   
  glTranslatef(positionF[0],positionF[1],positionF[2]);	//translating the position of the food based on x and y
  glScalef(0.05,0.05,0.05);	//scaling the object down to 7% its original size

  glBegin(GL_POLYGON);	//begin drawing the polygon
	for (int j = 0; j < 4; j++)	//for loop which will go through the 4 vertices of the food object
 	{
    glVertex3fv(vertices[j]);	//drawing the vertices using the positions stored in the vertices[] array
  }
	glEnd();	//finish drawing polygon

  // add fake shine (specular light) to food
  glPushMatrix();
  for (int j = 0; j < 2; j ++)
  {
    glTranslatef(shine,shine,0.0);
    for (int k = 0; k < 4; k ++)
    {
      glColor3f(0.9,0.9,0.9);
      glBegin(GL_POLYGON);
      glVertex3fv(specs[j][k]);
      glEnd();
    }
  }
  glPopMatrix();

	glPopMatrix();	//revert modelview matrix
}