#ifndef GUI_H
#define GUI_H

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
#include "TextureRenderer.h"

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
#include <string>
#include <vector>
#include <glfw3.h>
#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"
#endif

#include "Texture2D.h"
#include "Rect.h"




struct Object
{
	std::string name;
	Texture2D tex;
	Rect rect;
	glm::vec2 pos;
	glm::vec2 rotation;
};

struct BackgroundObject
{
	Texture2D tex;
	Rect rect;
	glm::vec2 pos;

};


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;




class GUI
{
public:
	GUI();
	GUI(GLFWwindow * window, TextureRenderer * rend);
	void init(GLFWwindow * window, TextureRenderer * rend);
	void draw();
	
	//GUI handlers. Done by Nuklear.
	struct nk_context *ctx;
	struct nk_colorf bg;
	~GUI();
private:
	
	bool showGMLayer = false;
	std::vector<Object> objects;
	std::vector<BackgroundObject> backgroundObjects;
	Texture2D background;
	TextureRenderer * renderer;
};

#endif