#ifndef __PACMAN_H__
#define __PACMAN_H__
#endif

class Pacman
{
public:
	float position[3];
	float direction[3];
	int lives_p;
	int score_p;
	float color_p[3];

	void drawPacman(void);
	void move(void);
	void changeDirection(int d);
	int getLives(void);
	int getScore(void);
	int getDirection(void);
	float getHeight(void);

	void deleteLife(void);
	void addScore(int);
};