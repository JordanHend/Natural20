#ifndef DNDRECT_H
#define DNDRECT_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);

	Rect(glm::vec4 xyAndwh);
	void setPos(glm::vec2 pos)
	{
		x = pos.x; y = pos.y;
	};
	glm::vec2 getPos()
	{
		return glm::vec2(x, y);
	};
	glm::vec4 getEverything()
	{
		return glm::vec4(x, y, w, h);
	}
	void setEverything(glm::vec4 evr)
	{
		this->x = evr.x;
		this->y = evr.y;
		this->w = evr.z;
		this->h = evr.w;
	}
	float scale = 1.0f;
	bool mouseOver(glm::vec2 mPos);
	float x = 0, y = 0, w = 0, h = 0;
	~Rect();
private:

	
};

#endif