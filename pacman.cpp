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

#include <stdio.h>

float position[3] = {4.0,2.0,6.0};
float direction[3] = {0,1,0};
int lives_p = 3;
int score_p = 0;
float color_p[3] = {1.0,1.0,0.0};
float mouth[3];

float angle_p = 0;

int Pacman::getDirection()
{
	for (int i = 0; i < 3; i ++)
	{
		if (direction[i] != 0)
			return direction[i] + i;
	}

	return 0;
}

float Pacman::getPosX(void)
{
	return position[0];
}

float Pacman::getPosY(void)
{
	return position[1];
}

int Pacman::getLives(void)
{
	return this->lives_p;
}

void Pacman::deleteLife(void)
{
	lives_p --;
}

int Pacman::getScore(void)
{
	return score_p;
}

void Pacman::addScore(int s)
{
	score_p += 10;
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

  if (lives_p >= 0)// || position[2] >= 6.0)
  {
    color_p[0] = 1.0;
    color_p[1] = 1.0;
    color_p[2] = 0.0;
  }
  else
  {
  	color_p[0] = 0.8;
  	color_p[1] = 0.8; 
  	color_p[2] = 0.8;
  }

  glColor3fv(color_p);

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
  glScalef(0.05,0.05,0.05);

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

void Pacman::reset(bool n)
{
	// reset color, position
	// new life, doesnt mean new game
	if (n)
	{
	//unless n == true
		lives_p = 3;
		score_p = 0;
	}
  position[0] = 4.0;
  position[1] = 2.0;
  position[2] = 6.0;
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
	// FIXME: pacman should only turn if there is no wall
	// FIXME: only turn if 1 - position < 0.01
	// left,right,up,down
	if ((int)position[0] * 2 % 2 <= 0.2 && (int)position[1] * 2 % 2 <= 0.2)
	{
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
}