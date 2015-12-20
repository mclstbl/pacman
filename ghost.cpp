#include "ghost.h"
#include <stdlib.h>	//including standard library
#include <math.h>	//including math functions
#include <stdio.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


float positionG[3] = {0.0,0.0,6.0};
float directionG[3] = {0,0,0};
float color[3];
int personality = 0;

Ghost::Ghost(int p)
{
	personality = p;
}

float Ghost::getPosXg(void)
{
	return positionG[0];// + 0.5;
}

float Ghost::getPosYg(void)
{
	return positionG[1];// - 0.5;
}

void Ghost::drawGhost(int wiggle)
{
  /*
  x = color
  o = white
  l = blue
  01234567890123
       xxxx
     xxxxxxxx
    xxxxxxxxxx
   xooxxxxooxxx
   ooooxxooooxx
   llooxxllooxx
  xllooxxllooxxx
  xxooxxxxooxxxx
  xxxxxxxxxxxxxx
  xxxxxxxxxxxxxx
  xxxxxxxxxxxxxx
  xxxxxxxxxxxxxx
  xx xxx  xxx xx
  x   xx  xx   x
*/

  float white[3] = {256,256,256};
  float blue[3] = {0.086,0.18,0.49};

  float vertices[20][4][3] = {
  	{{4,0,0},{9,0,0},{9,1,0},{4,1,0}},
  	{{2,-1,0},{10,-1,0},{10,0,0},{2,0,0}},
  	{{1,-2,0},{11,-2,0},{11,-1,0},{1,-1,0}},
  	{{0,-3,0},{12,-3,0},{12,-2,0},{0,-2,0}},
  	{{0,-4,0},{12,-4,0},{12,-3,0},{0,-3,0}},
  	{{0,-5,0},{12,-5,0},{12,-4,0},{0,-4,0}},
  	{{-1,-6,0},{13,-6,0},{13,-5,0},{-1,-5,0}},
  	{{-1,-7,0},{13,-7,0},{13,-6,0},{-1,-6,0}},
  	{{-1,-8,0},{13,-8,0},{13,-7,0},{-1,-7,0}},
  	{{-1,-9,0},{13,-9,0},{13,-8,0},{-1,-8,0}},
  	{{-1,-10,0},{13,-10,0},{13,-9,0},{-1,-9,0}},
  	{{-1,-11,0},{13,-11,0},{13,-10,0},{-1,-10,0}},

  	{{-1,-12,0},{1,-12,0},{1,-11,0},{-1,-11,0}},
  	{{2,-12,0},{5,-12,0},{5,-11,0},{2,-11,0}},
  	{{7,-12,0},{10,-12,0},{10,-11,0},{7,-11,0}},
  	{{11,-12,0},{13,-12,0},{13,-11,0},{11,-11,0}},

  	{{-1,-13,0},{0,-13,0},{0,-12,0},{-1,-12,0}},
  	{{3,-13,0},{5,-13,0},{5,-12,0},{3,-12,0}},
  	{{7,-13,0},{9,-13,0},{9,-12,0},{7,-12,0}},
  	{{12,-13,0},{13,-13,0},{13,-12,0},{12,-12,0}}
  };

  /*
   ooo
  ooooo
  ooooo
  ooooo
   ooo
  */

  float eye_w[10][4][3] = {
    {{1,-3,1},{3,-3,1},{3,-2,1},{1,-2,1}},
    {{0,-4,1},{4,-4,1},{4,-3,1},{0,-3,1}},
    {{0,-5,1},{4,-5,1},{4,-4,1},{0,-4,1}},
    {{0,-6,1},{4,-6,1},{4,-5,1},{0,-5,1}},
    {{1,-7,1},{3,-7,1},{3,-6,1},{1,-6,1}},


    {{7,-3,1},{9,-3,1},{9,-2,1},{7,-2,1}},
    {{6,-4,1},{10,-4,1},{10,-3,1},{6,-3,1}},
    {{6,-5,1},{10,-5,1},{10,-4,1},{6,-4,1}},
    {{6,-6,1},{10,-6,1},{10,-5,1},{6,-5,1}},
    {{7,-7,1},{9,-7,1},{9,-6,1},{7,-6,1}}
  };

  /*
  ll
  ll
  */

  float eye_b[2][4][3] = {
    {{0,-6,2},{2,-6,2},{2,-4,2},{0,-4,2}},
    {{6,-6,2},{8,-6,2},{8,-4,2},{6,-4,2}}
  };

  glColor3fv(color); 

  glPushMatrix();

	glTranslatef(positionG[0],positionG[1],positionG[2]);
	glScalef(0.03,0.03,0.03);
   
  for (int i = 0; i < 12; i ++)
  {
    glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++)
  	  {
        glVertex3fv(vertices[i][j]);
      }
    glEnd();
  }

  glPushMatrix();

  glTranslatef(wiggle,0,0);
  for (int i = 12; i < 20; i ++)
  {
    glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++)
  	  {
        glVertex3fv(vertices[i][j]);
      }
    glEnd();
  }
  glPopMatrix();

  glColor3fv(white);   
  for (int i = 0; i < 10; i ++)
  {
    glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++)
  	  {
        glVertex3fv(eye_w[i][j]);
      }
    glEnd();
  }

  glPushMatrix();

  glTranslatef(wiggle,0,0);
  glColor3fv(blue);
  for (int i = 0; i < 2; i ++)
  {
    glBegin(GL_POLYGON);
      for (int j = 0; j < 4; j++)
  	  {
        glVertex3fv(eye_b[i][j]);
      }
    glEnd();
  }
  
  glPopMatrix();
  glPopMatrix();
}

void Ghost::init(int p)
{
	// based on personality / behaviour specified in constructor
	// red, pink, blue, orange
 
  switch(p)
  {
    case 0:
      color[0] = 0.87;
      color[1] = 0;
      color[2] = 0.055;
      positionG[0] = 0.0;
      positionG[1] = 1.0;
      positionG[2] = 6.0;
      break;
    case 1:
      color[0] = 0.91;
      color[1] = 0.47;
      color[2] = 0.6;
      positionG[0] = 0.0;
      positionG[1] = 2.0;
      positionG[2] = 6.0;
      break;
    case 2:
      color[0] = 0.055;
      color[1] = 0.6;
      color[2] = 0.87;
      positionG[0] = 0.0;
      positionG[1] = 3.0;
      positionG[2] = 6.0;
      break;
    case 3:
      color[0] = 0.9;
      color[1] = 0.4;
      color[2] = 0;
      positionG[0] = 0.0;
      positionG[1] = 4.0;
      positionG[2] = 6.0;
      break;
    default:
      color[0] = 0.9;
      color[1] = 0.4;
      color[2] = 0;
      break;
  }
}

void Ghost::move(float x, float y)
{
	float move_size = 0.4 + 0.3 * pow(-1,rand() % 2) + 0.05 * pow(-1,rand() % 2);
	/*
	switch(personality)
	{
		case 0:
		//chaser
		  break;
		case 1:
		//ambusher
		  break;
		case 2:
		//fickle
		  break;
		case 3:
		//feigning ignorance
		  break;
		default:
		*/
		
		  float movX, movY;
		//  movX = move_size * x + (rand() % 2) / 100;
		//  movY = move_size * y + (rand() % 2) / 100;
/*
      int max = 5;
      if(movX > max)
      {
        directionG[0] = -1;
        directionG[1] = 0;
      }
      else if(movX < -1 * max)
      {
        directionG[0] = 1;
        directionG[1] = 0;
      }
      if(movY > max)
      {
        directionG[0] = 0;
        directionG[1] = -1;
      }
      else if(movY < -1 * max)
      {
        directionG[0] = 0;
        directionG[1] = 1;
      }
*/
		//	positionG[0] = move_size * x;
		//  positionG[1] = move_size * y;
		
//			break;
//	}
}