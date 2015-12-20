#ifndef __GHOST_H__
#define __GHOST_H__
#endif

class Ghost
{
public:
	Ghost(int);
	float positionG[3] = {0.0,0.0,6.0};
	float directionG[3] = {0,0,0};
	float color[3];
	int personality = 0;

  float getPosXg(void);
  float getPosYg(void);

	void drawGhost(int);
	void init(int);
	void move(float,float);
};