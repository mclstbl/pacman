//Defining the Food Header File
#ifndef __FOOD_H__
#define __FOOD_H__
#endif

class Food{	//Food Class
public:	//public access modifiers
	float positionF[3] = {0.0,0.0,6.0};	//setting position of the food
	float boundingBoxF[4] = {4,4,-4,-4};

	void setBoundsF(float,float,float,float);
	void drawFood(bool,int);	//drawFood Function declaration
};