#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glfw3.h>
extern int SCREEN_WIDTH, SCREEN_HEIGHT;
class Camera
{
public:
	Camera();
	glm::mat4 getViewMatrix();
	void handleDrag(int action, int lastX, int lastY, int newX, int newY);
	void handleKeys(int key, int scancode, int action, int mods);
	~Camera();
	glm::vec2 position = glm::vec2(0,0);
	const float SPEED = 20;
private:

	
	const glm::vec3 UP = glm::vec3(0, 1, 0);
	const glm::vec3 FORWARD = glm::vec3(0, 0, -1);
	glm::vec3 RIGHT = glm::vec3(1, 0, 0);
};

#endif