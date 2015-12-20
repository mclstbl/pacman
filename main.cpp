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
#include <string>

#include "pacman.h"
#include "ghost.h"
#include "food.h"
#include "text.h"
#include "walls.h"

using namespace std;

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
Text gameOverText,minusLife,newGameText,pressArrow,pauseT,newGameT,quitT,plusScore,unPauseT,scoreText,scoreNumber;

bool newFood = true;
bool paused = false;
bool newGame = false;
bool resetGame = true;
bool endG = false;
bool ghostHit = false;
bool foodHit = false;

int wiggleEyes = 1;
int timer = 1;

void endGame(void)
{
	//chars = new char[9];
	//chars = {'G','A','M','E',' ','O','V','E','R'};
	endG = true;
	newFood = false;
	ghostHit = false;
}

void loseLife(void)
{
	//chars = new char[18];
	//chars = {'Y','O','U',' ','L','O','S','T',' ','A',' ','L','I','F','E',' ',':','('};
	P1.deleteLife();
	ghostHit = true;
}

void reset(void)
{
  // pause game, await arrow press
  // generate new food position
  P1.reset(newGame); // true for newGame, false otherwise
	ghostHit = false;
	foodHit = false;
	resetGame = true;
	newFood = true;
}

bool wait(int n)
{
	// wait (n + timer)
	// wait maximum of n=10000
	// store current timer in wait
	// if timer + n == wait
	// 	stop wait
	if (n <= timer)
	{
		return true;
	}
 	return false;
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
    endGame();
  }
}

void printText(void)
{
	gameOverText.setText(0);
	minusLife.setText(1);
	newGameText.setText(2);
	pressArrow.setText(3);
	pauseT.setText(4);
	newGameT.setText(5);
	quitT.setText(6);
	plusScore.setText(7);
	scoreText.setText(8);
	unPauseT.setText(9);
 	std::string temp = std::to_string(P1.getScore());
	scoreNumber.setText(temp);
}

bool detectCollision(Ghost ghost,Pacman p)
{
  // check if p is close to ghost

  float limit;
  if (p.getDirection() == 2 && ghost.getPosXg() - p.getPosX() < 1) //means pacman is going up
  {
  	limit = 0.9;
  }
  else if (p.getDirection() == 0) //down
  {
  	limit = 0.1;
  }
  else if (abs(p.getDirection()) == 1) // pacman is going left or right
  {
  	limit = 0.8;
  }
  else
  {
  	limit = 0.4;
  }
	if(sqrt(pow(ghost.positionG[0] - p.position[0],2)	+ pow(ghost.positionG[1] - p.position[1],2)) < limit)
  {
    return true;
	}
	return false;
}

bool detectCollision(Food food,Pacman p)
{
	// check if p is close to food

  float limit = 0.5;
  if (p.getDirection() == 2) //means pacman is going up
  {
  	limit = 0.6;
  }
  else if (p.getDirection() == 0) //down
  {
  	limit = 0.3;
  }
  else if (abs(p.getDirection()) == 1) // pacman is going left or right
  {
  	limit = 0.5;
  }
  else
  {
  	limit = 0.4;
  }
	if (sqrt(pow(food1.positionF[0] - p.position[0],2) + pow(food1.positionF[1] - p.position[1],2)) < limit)
	{
    newFood = true;
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
		  if (!paused && resetGame) P1.changeDirection(0);
			break;

		case GLUT_KEY_RIGHT:
		  if (!paused && resetGame) P1.changeDirection(1);
			break;

		case GLUT_KEY_UP:
		  if (!paused && resetGame) P1.changeDirection(2);
			break;

		case GLUT_KEY_DOWN:
		  if (!paused && resetGame) P1.changeDirection(3);
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
	glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	W1.createList();
	chaser.init(0);
	ambusher.init(1);
	fickle.init(2);
	ignorance.init(3);
}

void idle(void)
{
  if (!paused)
  {
	  P1.move();
	  chaser.move(P1.getPosX(),P1.getPosY());
	  ambusher.move(P1.getPosX(),P1.getPosY());
	  fickle.move(P1.getPosX(),P1.getPosY());
	  ignorance.move(P1.getPosX(),P1.getPosY());
  }

  if (P1.getLives() < 0)
  {
   	die(P1); // food is not regenerated
  }
  else
  {
	  Ghost ghosts[4] = {chaser,ambusher,fickle,ignorance};

	  for (int i = 0; i < 4; i++)
	  {
	  	if (detectCollision(ghosts[i],P1))
	  	{
	  		loseLife();
	  		reset(); //new game triggered by life decrementi = 4; //break out of ghosts loop
	  	}
	  }

	  if (detectCollision (food1,P1))
	  {
	  	P1.addScore(10);
      foodHit = true;
	  }
  }

  if (timer % 20 == 0)
  {
  	wiggleEyes *= -1;
  	wiggleEyes ++;
  	//text.fade();
  }

  if (timer > 10000)
  {
  	timer = 1;
  }
  timer ++;

  printText();

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

	chaser.drawGhost(wiggleEyes);
	ambusher.drawGhost(wiggleEyes);
	fickle.drawGhost(wiggleEyes);
	ignorance.drawGhost(wiggleEyes);

  if (P1.getLives() >= 0)
  {
    food1.drawFood(newFood);
  }
 
  P1.drawPacman();

  W1.drawWalls();

  if(P1.getLives() < 0)
  {
 		gameOverText.drawText(0,0);
 	}
 	if(ghostHit)
 	{
		minusLife.drawText(0,0);
	}
	if(newGame)
 	{	
 		newGameText.drawText(-3,1);
 		pressArrow.drawText(-5,0);
 	}
 	if(paused)
 	{
 		unPauseT.drawText(-2,0);
 	}
 	if(foodHit)
 	{
 	 	plusScore.drawText(0,0);
 	}

 	scoreText.drawText(-3,7.5);
 	scoreNumber.drawText(0,7.5);

 	//instructions
 	pauseT.drawText(3,5);
 	newGameT.drawText(3,4.5);
 	quitT.drawText(3,4);

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(800, 0);

	glutCreateWindow("Pacman");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	init();

	glutMainLoop();

	return(0);
}