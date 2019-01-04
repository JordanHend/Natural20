#include "Camera.h"



Camera::Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 view;
	glm::vec2 midOffset = glm::vec2(SCREEN_WIDTH * 0.5 , SCREEN_HEIGHT * 0.5);

	view = glm::translate(view, glm::vec3(midOffset, 0.0));
	//view = glm::rotate(view, -this->rot, glm::vec3(0.0, 0.0, 1.0));
	view = glm::translate(view, glm::vec3(-midOffset, 0.0));
	view = glm::translate(view, glm::vec3(-this->position, z));

	return view;
}

void Camera::handleDrag(int action, int lastX, int lastY, int newX, int newY)
{
	if (action == GLFW_PRESS)
	{
		float xoffset = newX - lastX;
		float yoffset = newY - lastY;
		position += glm::vec2(-xoffset ,-yoffset);
	}
}


void Camera::handleKeys(int key, int scancode, int action, int mods)
{
}

Camera::~Camera()
{
}
