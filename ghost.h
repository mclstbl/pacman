#ifndef __GHOST_H__
#define __GHOST_H__
#endif

class Ghost
{
public:
	Ghost(int);
	float positionG[3];
	float directionG[3];
	float color[3];
	int personality;

	void drawGhost(void);
	void init(int);
	void move(float,float);
};