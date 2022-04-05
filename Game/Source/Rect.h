#ifndef __RECT_H__
#define __RECT_H__

class Rect
{
public:
	Rect(float x = 0, float y = 0, float w = 0, float h = 0) 
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

public:

	float x = 0, y = 0, w = 0, h = 0;
};

#endif //__RECT_H__