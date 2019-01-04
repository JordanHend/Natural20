#define DEBUG_H


#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 102



#include "Timer.h"
#include "ResourceManager.h"
#include "Camera.h"

//Math headers
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#ifndef NUK_H
#define NUK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <glfw3.h>
#include <glad\glad.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"
#endif

#include "GUI.h"
#include "Font.h"


//These members are usually extern'd into other files. I know this is bad practice but it's just the quickest way for now.
Font dFont;
int SCREEN_HEIGHT;
int SCREEN_WIDTH;
int MAP_WIDTH, MAP_HEIGHT;
glm::mat4 projection;
GLFWwindow * window;
Camera camera;


TextureRenderer * renderer;
Map map;


//Mouse input
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

bool mButtonDown = false;

//Process Keyboard input.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//Process mouse input.
void mouseCallback(GLFWwindow * window, double xposition, double yposition);
//Handle window size change event. 
void framebuffer_size_callback(GLFWwindow * window, int width, int height);
//Processes mouse scroll callbacks.
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//Initializes openGL
int initOpenGL();


float scale = 1.0f;


void APIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	//This can get annoying if it outputs for EVERYTHING-- only print when theres an error.
	if(type == GL_DEBUG_TYPE_ERROR)
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

int initOpenGL()
{
	//Init glfw
	glfwInit();
	//Set version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);


	//Creating window
#ifdef DEBUG_H

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dee&Dee", NULL, NULL);

#else
	window = glfwCreateWindow(mode->width, mode->height, "OpenGL", monitor, NULL);
	SCREEN_WIDTH = mode->width;
	SCREEN_HEIGHT = mode->height;
#endif


	if (window == NULL)
	{
		std::cout << "Failed to create window";
		return -1;
	}

	//Set context to current window
	glfwMakeContextCurrent(window);
	//Set event callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scroll_callback);
	//initialize GLAD function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 1;

}

void drawGrid()
{


}

void handleCameraKeyInput(float deltaTime)
{ 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.position -= glm::vec2(0, camera.SPEED *  0.1);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.position += glm::vec2(0, camera.SPEED *  0.1);
	}


	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.position -= glm::vec2(camera.SPEED *  0.1, 0);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.position += glm::vec2(camera.SPEED * 0.1, 0);
	}
}
GUI gui;
int main()
{
	//Initialize screen size.
	SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;

	//Init OpenGL
	initOpenGL();
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	camera.position = glm::vec2(0, 0);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	//Setting up shaders.
	ResourceManager::LoadShader("Shader/GridVertex.shdr", "Shader/GridFrag.shdr", nullptr, "grid");
	ResourceManager::LoadShader("Shader/sprite.vshdr", "Shader/sprite.fshdr", nullptr, "sprite");
	ResourceManager::LoadShader("Shader/textVertex.shdr", "Shader/textFragment.shdr", nullptr, "text");

	//Setting up Font
	dFont = Font("Font.ttf");

	//Getting shaders for some rendering being done here.
	Shader f = ResourceManager::GetShader("text");
	Shader s = ResourceManager::GetShader("sprite");

	//Init renderer
	renderer = new TextureRenderer(ResourceManager::GetShader("sprite"));

	//Map has reference to the renderer.
	map.setRenderer(renderer);


	//Create GUI
	gui.init(window, &map);

	//Timer for fps.
	Timer timer;
	timer.start();
	timer.unpause();
	float TimeBetweenFrames = 0, lastFrame = 0, FPS = 0;

	while (!glfwWindowShouldClose(window))
	{
		float deltaTime = timer.getTicks() / 1000;
		timer.start();
		float currentFrame = glfwGetTime();
		FPS = (1 / deltaTime);
		TimeBetweenFrames = (currentFrame - lastFrame);
		lastFrame = currentFrame;
		FPS = (1 / TimeBetweenFrames);


		//Move camera with wasd
		handleCameraKeyInput(deltaTime);

		//Handle logic of mouse clicks on map.
		map.logic();

	

		//Sprite shader
		s.use();
	

		//Draw gui (using nuklear)
		gui.draw();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Set view and projection to be the correct projection for screen space coordinates. 
		f.use();
		f.setMat4("view", glm::mat4(1));
		glm::mat4 proj = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);
		f.setMat4("projection", proj);

		//Render fps to screen space.
		dFont.RenderText(std::to_string(FPS), SCREEN_WIDTH - 120, 40, 0.2, glm::vec3(0.7, 0.7, 0.2), true);

		//Draw the map (objects on board and grid)
		map.draw();

		//Present gui
		nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

		//Swap buffers.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	
}

extern bool dragMap;
void mouseCallback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}



	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		bool onWindow = false;
		for (unsigned int i = 0; i < gui.windowBounds.size(); i++)
		{
			if (gui.windowBounds[i].mouseOver(glm::vec2( xpos, ypos)))
			{
				onWindow = true;
			}
		}
		if(!onWindow && dragMap)
		camera.handleDrag(GLFW_PRESS, lastX, lastY, xpos, ypos);
	}
	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	bool onWindow = false;
	for (unsigned int i = 0; i < gui.windowBounds.size(); i++)
	{
		if (gui.windowBounds[i].mouseOver(glm::vec2(lastX, lastY)))
		{
			onWindow = true;
		}
	}
	if (!onWindow)
	{
		
	 	scale += yoffset * 0.1;
		if (scale < 0.1)
			scale = 0.1;
	}


	glfw.scroll.x += (float)xoffset;
	glfw.scroll.y += (float)yoffset;

}
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width, SCREEN_HEIGHT = height;
};
