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
char* characters;

void Text::drawText(void)
{
  printf("%s\n", characters);
}

void Text::setText(char * c)
{
	this -> characters = c;
}