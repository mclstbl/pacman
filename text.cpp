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

float positionT[3] = {0,0,7.0};
const char* characters;


void Text::drawText(int length, float x , float y){
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRasterPos2f(x, y);
	for(int i=0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)characters[i]);
	}
	glPopMatrix();
}

void Text::setText(char * c){
	this -> characters = c;
}