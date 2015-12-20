#ifndef __PACMAN_H__
#define __PACMAN_H__
#endif

class Pacman
{
public:
	float position[3] = {4.0,2.0,6.0};
	float direction[3] = {0,1,0};
	int lives_p = 3;
	int score_p = 0;
	float color_p[3] = {1.0,1.0,0.0};
	float mouth[3];

	void drawPacman(void);
	void move(void);
	void changeDirection(int d);
	int getLives(void);
	int getScore(void);
	int getDirection(void);
	float getHeight(void);
	float getPosX(void);
	float getPosY(void);

  void reset(bool);
	void deleteLife(void);
	void addScore(int);
};