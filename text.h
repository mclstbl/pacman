#ifndef __TEXT_H__
#define __TEXT_H__
#endif

#include <string>
using namespace std;

class Text{
public:

	float positionT[3] = {0,0,7.0};
	char* characters;
	float colorT[4] = {0.7,0.7,0.7,1.0};
	int length = 0;

	void drawText(float,float);
	void setText(int,std::string);
	void setText(int);
	void fade(void);
};