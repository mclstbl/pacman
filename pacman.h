#ifndef __PACMAN_H__
#define __PACMAN_H__
#endif

class Pacman
{
public:
	float position[3];
	float direction[3];
	int lives;
	int score;

	void drawPacman(void);
	void move(void);
	void changeDirection(int d);
};