#ifndef __PACMAN_H__
#define __PACMAN_H__
#endif

class Pacman
{
public:
	float position[3] = {0.0,-4.0,6.0};
	float direction[3] = {0,1,0};
	int lives_p = 3;
	int score_p = 0;
	float color_p[3] = {1.0,1.0,0.0};
	float boundingBox[4] = {4,4,-4,-4};

	void drawPacman(int);
	void move(void);
	void changeDirection(int d);

	int getLives(void);
	int getScore(void);
	int getDirection(void);
	float getHeight(void);
	float getPosX(void);
	float getPosY(void);

	void setBounds(float,float,float,float);

  void reset(bool);
	void deleteLife(void);
	void addLife(void);
	void addScore(int);
};