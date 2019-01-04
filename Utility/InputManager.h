#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H


#define KEY_DOWN 1
#define KEY_UP 0

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glfw3.h>
#include <glad\glad.h>
class InputManager
{
public:
	InputManager();

	GLboolean  keys[1024];

	bool mouseButtonDown[2];
	double mousePos[2];

	void setLeftClick(bool val)
	{
		mouseButtonDown[0] = val;
	}

	void setRightClick(bool val)
	{
		mouseButtonDown[1] = val;
	}

	bool getLeftClick()
	{
		return mouseButtonDown[0];
	}

	bool getRightClick()
	{
		return mouseButtonDown[1];
	}

	bool isKeyDown(int key)
	{
		return keys[key];
	}

	void setKeyDown(int key)
	{
		keys[key] = KEY_DOWN;
	}

	void setKeyUp(int key)
	{
		keys[key] = KEY_UP;
	}

	void handleKeyInput(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = KEY_DOWN;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = KEY_UP;
		}
	}


	void handleMouseInput(double x, double y)
	{
		mousePos[0] = x; mousePos[1] = y;
	}

	glm::vec2 getMousePos()
	{
		return glm::vec2(mousePos[0], mousePos[1]);
	}


	

	~InputManager();
};

#endif