#include "text.h"

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
#include <string>

float positionT[3] = {0,0,7.0};
const char* characters;
float colorT[4] = {0.7,0.7,0.7,1.0};
int length = 0;

void Text::drawText(float x , float y){
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRasterPos2f(x, y);
	glScalef(1,1,1);
	glTranslatef(0,0,10);
	glColor4fv(colorT);
	for(int i=0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)characters[i]);
	}
	glPopMatrix();
}

void Text::setText(int l, string c)
{
	length = l;
	characters = (char* )(c.c_str());
}

void Text::setText(int c)
{
  switch (c)
  {
  	case 0:
  	  length = 9;
  	  characters = "GAME OVER";
  		break;
  	case 1:
  	  length = 2;
   	  characters = "-1";
  		break;
  	case 2:
  		length = 8;
  		characters = "NEW GAME";
  		break;
  	case 3:
  		length = 25;
  		characters = "PRESS ARROW KEYS TO START";
  		break;
  	case 4:
  		length = 17;
  		characters = "P - PAUSE/UNPAUSE";
  		break;
  	case 5:
  		length = 12;
  		characters = "N - NEW GAME";
  		break;
  	case 6:
  		length = 8;
  		characters = "Q - QUIT";
  		break;
  	case 7:
  		length = 3;
  		characters = "+10";
  		break;
  	case 8:
  		length = 6;
  		characters = "SCORE ";
  		break;  	
  	case 9:
    	length = 18;
    	characters = "Press P to unpause";
    	break;
  }
}

void Text::fade(void){
	// decrement alpha value
	this -> colorT[3] -= 0.05;
}