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
#include <stdlib.h>

float position[3] = {0.0,0.0,6.0};
float direction[3] = {0,1,0};
int lives = 3;
int score = 0;

void Pacman::draw(void)
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

    printf("%f %f %f\n", position[0],position[1],position[2]);

    glColor3f(1.0,1.0,0.0);    

    //glTranslatef(0,0,6);
	  glTranslatef(position[0],position[1],position[2]);
	  glScalef(0.05,0.05,0.05);
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

    for (int i = 0; i < 13; i ++)
    {
  	  glBegin(GL_POLYGON);
  	    for (int j = 0; j < 4; j++)
  	    {
          glVertex3fv(vertices[i][j]);
        }
  	  glEnd();
  	}
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