#ifndef __TEXT_H__
#define __TEXT_H__
#endif

class Text
{
public:
	float positionT[3];
	char* characters;

	void drawText(void);
	void setText(char * c);
};