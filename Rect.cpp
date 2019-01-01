#include "Rect.h"



Rect::Rect()
{
}

Rect::Rect(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::Rect(glm::vec4 xyAndwh)
{
	this->x = xyAndwh.x;
	this->y = xyAndwh.y;
	this->w = xyAndwh.z;
	this->h = xyAndwh.w;
}


bool Rect::mouseOver(glm::vec2 mPos)
{
	float px = mPos.x, py = mPos.y;

	float rx = x * scale;
	float ry = y * scale;
	float rw = w * scale;
	float rh = h * scale;

	if (px >= rx &&       
		px <= rx + rw &&   
		py >= ry &&        
		py <= ry + rh) {  
		return true;
	}
	return false;
}

Rect::~Rect()
{
}
