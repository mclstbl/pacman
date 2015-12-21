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
Text gameOverText,minusLife,newGameText,pressArrow,pauseT,newGameT,quitT,plusScore,unPauseT,scoreText;

bool newFood = true;
bool paused = false;
bool newGame = false;
bool resetGame = true;
bool endG = false;
bool ghostHit = false;
bool foodHit = false;
bool plusLife = true;

int wiggleEyes = 1;
int timer = 1;
int wait_v; // change this value to current timer + n to wait
bool cur_wait;

float bx1,by1,bx2,by2;

void endGame(void)
{
	endG = true;
	newFood = false;
	ghostHit = false;
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
/*
	newFood = true;
	paused = true;
	newGame = true;
	endG = false;
	ghostHit = false;
	foodHit = false;
	plusLife = false;
*/
	chaser.init(0);
	ambusher.init(1);
	fickle.init(2);
	ignorance.init(3);
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
		case 'q':
		case 27:
			exit (0);
			break;

		case 'p':
			if (!endG)
			{
		  	paused = !paused;
		  }
		  break;

		case 'n':
		  newGame = true;
		  P1.reset(newGame);
		  endG = false;
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


  if (!paused && cur_wait || foodHit && !paused) //paused and waiting
  {
  	wait_v = 0;
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

	if (newGame)
	{
		P1.reset(newGame);
		reset();
	}

  if(!cur_wait && wait_v - timer <= 1)
  {
 // 	foodHit = false;
  }

  if (timer % 20 == 0)
  {
  	wiggleEyes *= -1;
  	wiggleEyes ++;
  	//text.fade();
  }

  if (timer > 10000)
  {
  	//timer = 1;
  }
  timer ++;

  if (P1.getScore() % 100 == 0 && P1.getScore() > 0 && plusLife)
  {
  	P1.addLife();
  	plusLife = false;
  }

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

/*
bool newFood = true;
bool paused = false;
bool newGame = false;
bool resetGame = true;
bool endG = false;
bool ghostHit = false;
bool foodHit = false;
bool plusLife = true;
*/

	boundaryBox(bx1 + 1.5,by1 + 2.7,bx2 - 2.7,by2 - 2.7);

  P1.drawPacman(wiggleEyes);

	chaser.drawGhost(wiggleEyes);
	ambusher.drawGhost(wiggleEyes);
	fickle.drawGhost(wiggleEyes);
	ignorance.drawGhost(wiggleEyes);

  if (P1.getLives() >= 0)
  {
    food1.drawFood(newFood,wiggleEyes % 2);
  }
 

  W1.drawWalls();

  if(P1.getLives() < 0 && !newGame)
  {
 		gameOverText.drawText(0,0);
 	}
 	glColor3f(0,1,0);
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
 	if(foodHit && !cur_wait)
 	{
 	 	//plusScore.drawText(0,0);
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
 		countdown.drawText(0,0);
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
	
	W1.createList();
<<<<<<< HEAD
	
=======

>>>>>>> a2d4bad2ae191bbaec3bd4b724746d339ebcb396
	glutMainLoop();

	return(0);
}
