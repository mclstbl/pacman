#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "pacman.h"
#include "ghost.h"
#include "food.h"
#include "text.h"
#include "walls.h"

float verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };

float pos[] = {0,1,0};
float rot[] = {0, 0, 0};
float headRot[] = {0, 0, 0};
// this one works to view multiple cube faces
// float camPos[] = {10, 10, 20};
// flat view
float camPos[] = {0, 0, 20};

float angle = 0.0f;

Walls W1;
Pacman P1;
Ghost chaser = Ghost(0);
Ghost ambusher = Ghost(1);
Ghost fickle = Ghost(2);
Ghost ignorance = Ghost(3);
Food food1;
bool newFood = true;
bool paused = true;
bool newGame = false;
int lives;

void endGame(void)
{
	Text text;
	char chars[9] = {'G','A','M','E',' ','O','V','E','R'};
	text.setText(chars);
	text.drawText(9,-1,8);
}

void loseLife(void)
{
	Text text;
	char chars[] = {};
	text.setText(chars); // 	printf("You lost a life\n");
	text.drawText(9,-1,8);
	P1.deleteLife();
}

void reset(void)
{
  // pause game, await arrow press
  // generate new food position
  P1.reset(newGame); // true for newGame, false otherwise
	paused = true;
	newFood = true;
	Text text;
	char chars[] = {};
	text.setText(chars);
	text.drawText(9,-1,8);
}

void die(Pacman p)
{
	if (P1.position[2] >= -60)
  {
  //	P1.position[2]--;
  }
  // pause until new game
  else
  {
    paused = true;
    endGame();
  }
}

bool detectCollision(Ghost ghost,Pacman p)
{
  // check if p is close to ghost
  // FIXME: ghost collision doesn't pause the game

	if
	(
		sqrt(
			pow(ghost.positionG[0] - p.position[0],2)
			+ 
			pow(ghost.positionG[1] - p.position[1],2)
		)
	  < 1
	)
  {
		printf("ghost collision detected %d lives left\n", P1.getLives());
    return true;
	}
	return false;
}

bool detectCollision(Food food,Pacman p)
{
	// check if p is close to food

	// sometimes doesnt work when
	// F  p
	// FIXME: pacman has trouble eating food when food is to the left

	if
	(
		sqrt(
			pow(food1.positionF[0] - p.position[0],2)
			+ 
			pow(food1.positionF[1] - p.position[1],2)
		)
	  < 2
	)
	{
    newFood = true;
    printf("food collision detected\n");
    return true;
	}
	newFood = false;
	return false;
}

/*
bool detectCollision(Wall wall,Pacman p)
{
	// check if p is close to wall, prevent from moving

	if(fabs(food1.positionF[0] - p.position[0]) < p.getHeight() / 3 && 
		 fabs(food1.positionF[1] - p.position[1]) < p.getHeight() / 2)
	{
    newFood = true;
    printf("food collision detected\n");
    return true;
	}
	newFood = false;
	return false;
}
*/

void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}

void cube(float v[8][3])
{
	glColor3fv(cols[1]);
	drawPolygon(0, 3, 2, 1, v);

	glColor3fv(cols[2]);
	drawPolygon(1, 0, 4, 5, v);

	glColor3fv(cols[3]);
	drawPolygon(5, 1, 2, 6, v);
	
	glColor3fv(cols[4]);
	drawPolygon(2, 3, 7, 6, v);
	
	glColor3fv(cols[5]);
	drawPolygon(6, 5, 4, 7, v);

	glColor3fv(cols[0]);
	drawPolygon(4, 0, 3, 7, v);
}

void drawBox(float* c, float w, float h, float d)
{
	float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]+d/2}, 
							 {c[0]-w/2, c[1]-h/2, c[2]-d/2}, 
							 {c[0]-w/2, c[1]+h/2, c[2]-d/2}, 
							 {c[0]+w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]-d/2} };

	cube(vertices);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;

		case 'p':
		  paused = !paused;
		  break;

		case 'n':
		  newGame = true;
		  break;
			
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
		  P1.changeDirection(0);
		  if (paused) paused = false;
			break;

		case GLUT_KEY_RIGHT:
		  P1.changeDirection(1);
		  if (paused) paused = false;
			break;

		case GLUT_KEY_UP:
		  P1.changeDirection(2);
		  if (paused) paused = false;
			break;

		case GLUT_KEY_DOWN:
		  P1.changeDirection(3);
		  if (paused) paused = false;
			break;
	}
	glutPostRedisplay();
}

void init(void)
{    
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	glEnable(GL_DEPTH_TEST);

	W1.createList();
	lives = P1.getLives();
	chaser.init(0);
	ambusher.init(1);
	fickle.init(2);
	ignorance.init(3);
}

void idle(void)
{
  P1.move();
  //chaser.move();)
  //ambusher.move();
  //fickle.move();
  //ignorance.move();

  if (lives - P1.getLives() > 3)
  {
   	die(P1); //game is paused indefinitely
   	//FIXME: add keyboard function that starts a new game
  }
  
  Ghost ghosts[4] = {chaser,ambusher,fickle,ignorance};

  for (int i = 0; i < 4; i++)
  {
  	if (detectCollision(ghosts[i],P1))
  	{
  		loseLife();
  		reset(); //new game triggered by life decrement
  	  i = 4; //break out of ghosts loop
  	}
  }

  if (detectCollision (food1,P1))
  {
  	P1.addScore(10);
  }
  
	glutPostRedisplay();
}

void display(void)
{
	float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glColor3f(1,1,1);

	//drawBox(origin, 10, 10, 10);
  
  W1.drawWalls();

	chaser.drawGhost();
	ambusher.drawGhost();
	fickle.drawGhost();
	ignorance.drawGhost();

  if (lives - P1.getLives() <= 3)
  {
    food1.drawFood(newFood);
  }
 
  //printf("%d\n", P1.getLives());
  //printf("%f %f %f\n", P1.getPosX(), P1.getPosY(), P1.getPosZ());

  P1.drawPacman();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(800, 0);

	glutCreateWindow("Pacman");

	glutDisplayFunc(display);
  if (paused)
  {
	  glutIdleFunc(idle);
	}
	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	init();

	glutMainLoop();

	return(0);
}
