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

using namespace std;

float verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };

float pos[] = {0,1,0};
float rot[] = {0, 0, 0};
float headRot[] = {0, 0, 0};
float camPos[] = {0, 0, 20};

float angle = 0.0f;

//Walls W1;
Pacman P1;
Ghost chaser = Ghost(0);
Ghost ambusher = Ghost(1);
Ghost fickle = Ghost(2);
Ghost ignorance = Ghost(3);
Food food1;
Text gameOverText,minusLife,newGameText,pressArrow,pauseT,newGameT,quitT,plusScore,unPauseT,scoreText;

bool newFood = true;
bool paused = false;
bool newGame = true;
bool resetGame = true;
bool endG = false;
bool ghostHit = false;
bool foodHit = false;
bool plusLife = true;
bool ghostChase = false;

int wiggleEyes = 1;
int timer = 1;
int wait_v; // change this value to current timer + n to wait
bool cur_wait;

std::string bonusColor = "BLUE";
int bonusPoints = 100;
bool bonusHit = false;
int bonusTime = 10;
int bonusGhost = 0;
bool bonusInit = false;

float bx1,by1,bx2,by2;

int WALLS_X = 31;
int WALLS_Y = 28;

int Walls_array[31][28] =
  { 
	{ 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 7, 0, 8, 1, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 1, 7, 0, 8, 1, 1, 7, 0, 6 },
	{ 6, 0, 2, 11, 11, 4, 0, 2, 11, 11, 11, 4, 0, 2, 4, 0, 2, 11, 11, 11, 4, 0, 2, 11, 11, 4, 0, 6 },
	{ 6, 0, 9, 3, 3, 10, 0, 9, 3, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 3, 10, 0, 9, 3, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 7, 0, 8, 7, 0, 8, 1, 1, 1, 1, 1, 1, 7, 0, 8, 7, 0, 8, 1, 1, 7, 0, 6 },
	{ 6, 0, 9, 3, 3, 10, 0, 2, 4, 0, 9, 3, 3, 11, 11, 3, 3, 10, 0, 2, 4, 0, 9, 3, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 6 },
	{ 9, 5, 5, 5, 5, 7, 0, 2, 11, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 11, 4, 0, 8, 5, 5, 5, 5, 10 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 11, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 11, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 8, 5, 5, 1, 1, 5, 5, 7, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 5, 5, 5, 5, 5, 10, 0, 9, 10, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 9, 10, 0, 9, 5, 5, 5, 5, 5 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 5, 5, 5, 5, 7, 0, 8, 7, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 8, 7, 0, 8, 5, 5, 5, 5, 5 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 9, 5, 5, 5, 5, 5, 5, 10, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0, 2, 4, 0, 8, 1, 1, 1, 1, 1, 1, 7, 0, 2, 4, 0, 6, 0, 0, 0, 0, 0 },
	{ 8, 5, 5, 5, 5, 10, 0, 9, 10, 0, 9, 3, 3, 11, 11, 3, 3, 10, 0, 9, 10, 0, 9, 5, 5, 5, 5, 7 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 7, 0, 8, 1, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 1, 7, 0, 8, 1, 1, 7, 0, 6 },
	{ 6, 0, 9, 3, 11, 4, 0, 9, 3, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 3, 10, 0, 2, 11, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 6 },
	{ 2, 1, 7, 0, 2, 4, 0, 8, 7, 0, 8, 1, 1, 1, 1, 1, 1, 7, 0, 8, 7, 0, 2, 4, 0, 8, 1, 4 },
	{ 2, 3, 10, 0, 9, 10, 0, 2, 4, 0, 9, 3, 3, 11, 11, 3, 3, 10, 0, 2, 4, 0, 9, 10, 0, 9, 3, 4 },
	{ 6, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 6 },
	{ 6, 0, 8, 1, 1, 1, 1, 11, 11, 1, 1, 7, 0, 2, 4, 0, 8, 1, 1, 11, 11, 1, 1, 1, 1, 7, 0, 6 },
	{ 6, 0, 9, 3, 3, 3, 3, 3, 3, 3, 3, 10, 0, 9, 10, 0, 9, 3, 3, 3, 3, 3, 3, 3, 3, 10, 0, 6 },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10 }
	};

GLubyte list[5];

void drawWalls (void)
{
	glColor3f(0, 0, 1);

	for (int I = 0; I < WALLS_X; I++)
	{
		for (int j = 0; j < WALLS_Y / 2; j++)
		{
			glColor3f(0, 0, 1);
			int call_this = 0;

			glPushMatrix();
			glTranslatef(-(float)WALLS_X / 2.0f, -(float)WALLS_Y / 2.0f, 0);

			glTranslatef(j, WALLS_Y - I, 0);

			glPushMatrix();
			glTranslatef(0.5, 0.5, 0);

			switch (Walls_array[I][j])
			{
				case 4:
					glRotatef(90.0, 0, 0, 1);
				case 3:
					glRotatef(90.0, 0, 0, 1);
				case 2:
					glRotatef(90.0, 0, 0, 1);
				case 1:
					call_this = 1;
					break;
				case 6:
					glRotatef(90.0, 0, 0, 1);
				case 5:
					call_this = 2;
					break;
				case 10:
					glRotatef(90.0, 0, 0, 1);
				case 9:
					glRotatef(90.0, 0, 0, 1);
				case 8:
					glRotatef(90.0, 0, 0, 1);
				case 7:
					call_this = 3;
					break;
			}

			glScalef(1, 1, 0.5);
			glTranslatef(-0.5, -0.5, 0);
			glCallList(list[call_this]);
			glPopMatrix();

			if (call_this != 0 || Walls_array[I][j] == 11)
			{
				glTranslatef(0, 0, -0.5);
				glCallList(list[4]);
			}
			glPopMatrix();
		}
	}

	int I;

	for (I = 0; I< WALLS_X; I++)
	{
		for (int j = WALLS_Y - 1; j >= WALLS_Y / 2; j--)
		{
			glColor3f(0, 0, 1);
			int call_this = 0;

			glPushMatrix();

			glTranslatef(-(float)WALLS_X / 2.0f, -(float)WALLS_Y / 2.0f, 0);
			glTranslatef(j, WALLS_Y - I, 0);

			glPushMatrix();
			glTranslatef(0.5, 0.5, 0);
			switch (Walls_array[I][j])
			{
			case 4:
				glRotatef(90.0, 0, 0, 1);
			case 3:
				glRotatef(90.0, 0, 0, 1);
			case 2:
				glRotatef(90.0, 0, 0, 1);
			case 1:
				call_this = 1;
				break;
			case 6:
				glRotatef(90.0, 0, 0, 1);
			case 5:
				call_this = 2;
				break;
			case 10:
				glRotatef(90.0, 0, 0, 1);
			case 9:
				glRotatef(90.0, 0, 0, 1);
			case 8:
				glRotatef(90.0, 0, 0, 1);
			case 7:
				call_this = 3;
				break;
			}
			glScalef(1, 1, 0.5);
			glTranslatef(-0.5, -0.5, 0);
			glCallList(list[call_this]);
			glPopMatrix();

			if (call_this != 0 || Walls_array[I][j] == 11)
			{
				glTranslatef(0, 0, -0.5);
				glCallList(list[4]);
			}
			glPopMatrix();
		}
	}
}

void createList()
{
	list[1] = glGenLists(1);

	glNewList(list[1], GL_COMPILE);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 1.0);
	glEnd();

	glEndList();

	list[2] = glGenLists(1);
	glNewList(list[2], GL_COMPILE);

	glBegin(GL_QUADS);

	glColor3f(0, 0, 1);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 1.0);

	glColor3f(0, 0, 1);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glEndList();

	list[3] = glGenLists(1);

	glNewList(list[3], GL_COMPILE);
	glBegin(GL_QUADS);

	glColor3f(0, 0, 1);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 1.0);

	glColor3f(0, 0, 1);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glEndList();

	list[4] = glGenLists(1);

	glNewList(list[4], GL_COMPILE);
	glBegin(GL_QUADS);

	glColor3f(0, 0, 1);
	glNormal3f(1.0, 0.0, 1.0);
	glVertex3f(1, 1, 1.0);
	glVertex3f(0, 1, 1.0);
	glVertex3f(0, 0, 1.0);
	glVertex3f(1, 0, 1.0);
	glEnd();
	glEndList();
}

void endGame(void)
{
	endG = true;
	newFood = false;
//	ghostHit = false;
}

void loseLife(void)
{
	P1.deleteLife();
	ghostHit = true;
}

void reset(void)
{
  // pause game, await arrow press
  // generate new food position
  // P1.reset(newGame); // true for newGame, false otherwise
	ghostHit = false;
	foodHit = false;
	resetGame = true;
	newFood = true;
	wait_v = timer + 250;

	chaser.init(0);
	ambusher.init(1);
	fickle.init(2);
	ignorance.init(3);

	P1.setBounds(bx1,by1,bx2,by2);
	food1.setBoundsF(bx1,by1,bx2,by2);
	chaser.setBoundsG(bx1,by1,bx2,by2);
	ambusher.setBoundsG(bx1,by1,bx2,by2);
	fickle.setBoundsG(bx1,by1,bx2,by2);
	ignorance.setBoundsG(bx1,by1,bx2,by2);
}

bool wait(void)
{
	// set wait_v to current timer + n
	// wait maximum of n=10000
	if (wait_v <= timer || wait_v == 0)
	{
		return true;
	}
 	return false;
}

void die(Pacman p)
{
  endGame();
}

int intLength(int n, int s)
{
	if (n <= 0)
	{
		return s + 1;
	}
	return intLength(n / 10, s + 1);
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
}

void boundaryBox(float x1, float y1, float x2, float y2){
	glColor3f(1,1,1);
	float points[4][3] = {
		{x2,y1,0},
		{x1,y1,0},
		{x1,y2,0},
		{x2,y2,0}
	};

	for(int i = 0; i < 4; i++)
	{
		glBegin(GL_LINES);
		glVertex3fv(points[i]);
		glVertex3fv(points[(i + 1) % 4]);
		glEnd();
	}
}

bool detectCollision(Ghost ghost,Pacman p)
{
  // check if p is close to ghost

  float limit;
  if (p.getDirection() == 2 && ghost.getPosXg() - p.getPosX() < 1) //means pacman is going up
  {
  	limit = 0.5;
  }
  else if (p.getDirection() == 0) //down
  {
  	limit = 0.2;
  }
  else if (abs(p.getDirection()) == 1) // pacman is going left or right
  {
  	limit = 0.3;
  }
  else
  {
  	limit = 0.2;
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
  	limit = 0.7;
  }
  else if (abs(p.getDirection()) == 1) // pacman is going left or right
  {
  	limit = 0.65;
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

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'Q':
		case 'q':
		case 27:
			exit (0);
			break;

		case 'P':
		case 'p':
			if (!endG)
			{
		  	paused = !paused;
		  }
		  break;

		case 'N':
		case 'n':
		  newGame = true;
		  P1.reset(newGame);
		  newFood = false;
		  //endG = false;
		  break;

		case 'G':
		case 'g':
			// cheat ;)
			printf("ghost chase started\n");
			ghostChase = true;
			bonusHit = false;
			break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			if (newGame && !newFood) newFood = true, newGame = false;
		  if (!paused && resetGame) P1.changeDirection(0);
			break;

		case GLUT_KEY_RIGHT:
			if (newGame && !newFood) newFood = true, newGame = false;
		  if (!paused && resetGame) P1.changeDirection(1);
			break;

		case GLUT_KEY_UP:
			if (newGame && !newFood) newFood = true, newGame = false;
		  if (!paused && resetGame) P1.changeDirection(2);
			break;

		case GLUT_KEY_DOWN:
			if (newGame && !newFood) newFood = true, newGame = false;
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

	//W1.createList();

	chaser.init(0);
	ambusher.init(1);
	fickle.init(2);
	ignorance.init(3);

	bx1 = 2;
	by1 = 5;
	bx2 = -5;
	by2 = -5;

	P1.setBounds(bx1,by1,bx2,by2);
	food1.setBoundsF(bx1,by1,bx2,by2);
	chaser.setBoundsG(bx1,by1,bx2,by2);
	ambusher.setBoundsG(bx1,by1,bx2,by2);
	fickle.setBoundsG(bx1,by1,bx2,by2);
	ignorance.setBoundsG(bx1,by1,bx2,by2);
}

void idle(void)
{
	cur_wait = wait(); //constantly check if system is waiting

  if (((!paused && cur_wait) || (foodHit && !paused)) && !newGame)
  // if not paused & not waiting || food is eaten & not paused || not a new game
  // let characters move
  {
  	wait_v = 0;
	  P1.move();
	  chaser.move(P1.getPosX(),P1.getPosY());
	  ambusher.move(P1.getPosX(),P1.getPosY());
	  fickle.move(P1.getPosX(),P1.getPosY());
	  ignorance.move(P1.getPosX(),P1.getPosY());
  }

  // check for collisions here
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
	  		newGame = false;
	  		reset(); //new game triggered by life decrement
	  		P1.reset(newGame);
	  		i = 4; //break out of ghosts loop
	  	}
	  }

	  if (detectCollision (food1,P1))
	  {
	  	P1.addScore(10);
	  	if (P1.getScore() % 100 == 0)
	  	{
	  		plusLife = true;
	  	}
      foodHit = true;
      wait_v = timer + 200;
	  }
  }

  // for testing, can be triggered with g key
  if(ghostChase || (((timer + (rand() % 1000) % 1000 == 0)) && rand() % 2 == 1))
  {
  	printf("in main collision loop\n");
  	if (!bonusInit)
  	{
  		printf("initializing bonus round\n");
  		//create bonus
  		bonusInit = true;
  		bonusTime = 1000 + rand() % 1000; //print countdown later
  		bonusPoints = rand () % 1000;
  		bonusPoints = 10 * (int) bonusPoints / 10; //make sure it's a factor of 10
  		bonusHit = false;
  		bonusGhost = rand() % 4;
  		wait_v = timer + bonusTime;
  	}
  }

  cur_wait = wait();

  if((ghostChase && !cur_wait) && !bonusHit)
  // bonus time is running && bonus has not been hit && waiting for timer
  {
  	 printf ("detecting bonus collision\n");
  	switch (bonusGhost)
  	{
  		//red pink blue orange
  		case 0:
  			bonusColor = "RED";
  			if(detectCollision(chaser,P1))
  			{
  				P1.addScore(bonusPoints);
  				bonusHit = true;
  				wait_v = 0;
  			}
  			break;
  		case 1:
  			bonusColor = "PINK";
  			if(detectCollision(ambusher,P1))
  			{
  				P1.addScore(bonusPoints);
  				bonusHit = true;
  				wait_v = 0;
  			}
  			break;
  		case 2:
  			bonusColor = "BLUE";
  			if(detectCollision(fickle,P1))
  			{
  				P1.addScore(bonusPoints);
  				bonusHit = true;
  				wait_v = 0;
  			}
  			break;
  		case 3:
  			bonusColor = "ORANGE";
  			if(detectCollision(ignorance,P1))
  			{
  				P1.addScore(bonusPoints);
  				bonusHit = true;
  				wait_v = 0;
  			}
  			break;
  	}
  }
  else
  {
  	wait_v = 0;
  	bonusInit = false;
  	bonusHit = false;
  }

  if (timer % 20 == 0)
  {
  	wiggleEyes *= -1;
  	wiggleEyes ++;
  }

  if (P1.getScore() % 100 == 0 && P1.getScore() > 0 && plusLife)
  {
  // add life for every 100 points
  	P1.addLife();
  	plusLife = false;
  }

  printText(); // update text

  timer ++;

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

	boundaryBox(bx1 + 1.5,by1 + 2.7,bx2 - 2.7,by2 - 2.7);

  P1.drawPacman(wiggleEyes);

	chaser.drawGhost(wiggleEyes);
	ambusher.drawGhost(wiggleEyes);
	fickle.drawGhost(wiggleEyes);
	ignorance.drawGhost(wiggleEyes);

	int offset = 9;

  if (P1.getLives() >= 0)
  {
    food1.drawFood(newFood,wiggleEyes % 2);
  }

//  W1.drawWalls();

  if(P1.getLives() < 0 && !newGame)
  {
 		gameOverText.drawText(offset -2,0);
 	}
 	glColor3f(0,1,0);
	if(newGame)
 	{	
 		newGameText.drawText(offset-3,1);
 		pressArrow.drawText(offset-5,0);
 	}
 	if(paused)
 	{
 		unPauseT.drawText(offset-4,0);
 	}

	glColor3f(1,1,1);
 	scoreText.drawText(-3,7.8);
 	
 	Text scoreNumber;
	int l;
	std::string temp;
	temp = std::to_string(P1.getScore());
 	l = intLength (P1.getScore(),0);
	scoreNumber.setText(l,temp);
	glColor3f(1,1,1);
 	scoreNumber.drawText(-1,7.8);

 	glColor3f(1,1,1);
 	if(!cur_wait && !foodHit && !paused && !endG)
	{
		Text countdown;
		//print 3..2..1
		int diff = wait_v - timer;

		if(diff <= 70)
		{
			temp = std::to_string((int)0);
		}
		else if(diff <= 120)
		{
			temp = std::to_string((int)1);
		}
		else if(diff <= 170)
		{
			temp = std::to_string((int)2);
		}
		else
		{
			temp = std::to_string((int)3);
		}
 		l = 1;
		countdown.setText(l,temp);
 		countdown.drawText(offset-2,0);
 	}

 	glColor3f(1,1,1);
 	if((ghostChase && !cur_wait) && !bonusHit)//!foodHit && !paused && !endG)
	// (ghostChase is on and waiting for timer) & bonus has not been hit
	{
		//print messages on the side
		int diff = wait_v - timer;

		temp = "";
		temp = "EAT THE " + bonusColor + " GHOST FOR " + std::to_string(bonusPoints) + " POINTS";
 		l = 35;
		Text notification;
		notification.setText(l,temp);
 		notification.drawText(offset-6,-2);
	} 	

 	// instructions
 	glColor3f(1,1,1);
 	pauseT.drawText(4,5);
 	glColor3f(1,1,1);
 	newGameT.drawText(4,4.5);
 	glColor3f(1,1,1);
 	quitT.drawText(4,4);

 	// draw lives
 	for (int i = 0; i < P1.getLives(); i ++)
 	{
 		Pacman life;
 		glPushMatrix();
 		glRotatef(90.0,0.0,0.0,1.0);
 		glTranslatef(7.25,1.5 - i * 0.3,-4); //y,z,x
 		glScalef(0.5,0.5,1);
 		life.drawPacman(wiggleEyes);
 		glPopMatrix();
 	}
	
	glScalef(0.38,0.47,0.49);
	glTranslatef(-3.8,0.6,0);
	drawWalls();

	glutPostRedisplay();

	glutSwapBuffers();
}

void W_init()
{

	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60,1.33,0.005,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(-1.5, 0, 40, -1.5, 0, 0, 0.0f,1.0f,0.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutInitWindowSize(1200, 1200);
	glutInitWindowPosition(800, 0);

	glutCreateWindow("Pacman");
	
	W_init();
	
	glutDisplayFunc(display);

	createList();	

	glutIdleFunc(idle);
	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	init();

	glutMainLoop();

	return(0);
}
