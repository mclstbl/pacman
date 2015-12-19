#include "pacman.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

float position[3] = {0.0,0.0,6.0};
float direction[3] = {0,1,0};
int lives_p = 3;
int score_p = 0;
float angle_p = 0;
float color_p[3] = {1.0,1.0,0.0};

int Pacman::getDirection()
{
	for (int i = 0; i < 3; i ++)
	{
		if (this -> direction[i] != 0)
			return i;
	}

	return 0;
}

int Pacman::getLives(void)
{
	return this -> lives_p;
}

void Pacman::deleteLife(void)
{
	this -> lives_p --;
}

int Pacman::getScore(void)
{
	return this -> score_p;
}

void Pacman::addScore(int s)
{
	this -> score_p += 10;
}

float Pacman::getHeight(void)
{
  return (13 * 0.1);
}

void Pacman::drawPacman(void)
{
  /*
  012345678910
     xxxxx
   xxxxxxxxx
  xxxxxxxxxxx
  xxxxxxxxxxx
    xxxxxxxxx
       xxxxxx
          xxx
       xxxxxx
    xxxxxxxxx
  xxxxxxxxxxx
  xxxxxxxxxxx
   xxxxxxxxx
     xxxxx
  */

  if (position[2] >= 6)
  {
    glColor3fv(color_p);
  }
  else
  {
  	glColor3f(0.8,0.8,0.8);
  }

  float vertices[13][4][3] = {
  	{{3,0,0},{7,0,0},{7,1,0},{3,1,0}},
  	{{1,-1,0},{9,-1,0},{9,0,0},{1,0,0}},
   	{{0,-2,0},{10,-2,0},{10,-1,0},{0,-1,0}},
   	{{0,-3,0},{10,-3,0},{10,-2,0},{0,-2,0}},
   	{{2,-4,0},{10,-4,0},{10,-3,0},{2,-3,0}},
   	{{5,-5,0},{10,-5,0},{10,-4,0},{5,-4,0}},
   	{{8,-6,0},{10,-6,0},{10,-5,0},{8,-5,0}},
   	{{5,-7,0},{10,-7,0},{10,-6,0},{5,-6,0}},
   	{{2,-8,0},{10,-8,0},{10,-7,0},{2,-7,0}},
   	{{0,-9,0},{10,-9,0},{10,-8,0},{0,-8,0}},
   	{{0,-10,0},{10,-10,0},{10,-9,0},{0,-9,0}},
   	{{1,-11,0},{9,-11,0},{9,-10,0},{1,-10,0}},
   	{{3,-12,0},{7,-12,0},{7,-11,0},{3,-11,0}}
  };

  // pacman faces movement direction
  if (direction[0] == -1)
  {
  	//left
  	angle_p = 0;
  }
  else if (direction[0] == 1)
  {
  	//right
  	angle_p = 180;
  }
  else if (direction[1] == 1)
  {
  	//up
  	angle_p = 270;
  }
  else
  {
  	//down
  	angle_p = 90;
  }

  glPushMatrix();

  glTranslatef(position[0],position[1],position[2]);
  glRotatef(angle_p,0,0,1);
  glScalef(0.1,0.1,0.1);

  for (int i = 0; i < 13; i ++)
  {
    glBegin(GL_POLYGON);
	    for (int j = 0; j < 4; j++)
 	    {
        glVertex3fv(vertices[i][j]);
      }
	  glEnd();
	}
	glPopMatrix();
}

void Pacman::move(void)
{
	// pacman keeps moving, depending on direction value
	float move_size = 0.05;
	position[0] += direction[0] * move_size;
	position[1] += direction[1] * move_size;
	position[2] += direction[2] * move_size;
}

void Pacman::changeDirection(int d)
{
	// left,right,up,down
	switch(d)
	{
		case 0:
      direction[0] = -1;
      direction[1] = 0;
      direction[2] = 0;
		  break;
		case 1:
      direction[0] = 1;
      direction[1] = 0;
      direction[2] = 0;
		  break;
		case 2:
      direction[0] = 0;
      direction[1] = 1;
      direction[2] = 0;
		  break;
		case 3:
      direction[0] = 0;
      direction[1] = -1;
      direction[2] = 0;
		  break;
	}
}