#ifndef __GHOST_H__
#define __GHOST_H__
#endif

class Ghost
{
public:
	Ghost(int);
	float positionG[3] = {-2.0,0.0,6.0};
	float directionG[3] = {0,0,0};
	float color[3];
	int personality = 0;

	void setBoundsG(float,float,float,float);
	void setPositionG(float,float,float);

  float getPosXg(void);
  float getPosYg(void);

	void drawGhost(int);
	void init(int);
	void move(float,float);
	int getDirectionG();
private:
	float boundingBox[4] = {4,4,-4,-4};
};