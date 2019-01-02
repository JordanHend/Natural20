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


#include "TextureRenderer.h"
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
#include <string>
#include <vector>
#include <glfw3.h>
#include <glad\glad.h>


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
#include "OpenFile.h"
#include "ResourceManager.h"
#include "Map.h"



extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#define GM_LAYER 0
#define PLAYER_LAYER 1




class GUI
{
public:
	GUI();
	GUI(GLFWwindow * window, Map * map);
	void init(GLFWwindow * window, Map * map);
	void draw();
	
	std::vector<Rect> windowBounds;

	//GUI handlers. Done by Nuklear.
	struct nk_context *ctx;
	struct nk_colorf bg;
	~GUI();
private:
	
	Map * map;

	int defaultLayer = 0;
	bool showGMLayer = false;
	std::vector<Token> tokens;

	struct NewObjectInfo
	{
		std::string name;
		std::string texture;
		int layer = 0;
	};

	char mapnamebuff[20];
	char xbuff[6], ybuff[6];
	void renderMenuBar();


	
	std::vector<Rect> bounds;


	bool mainPanelInBackground = false;

	bool newMapWindow = false;
	void renderNewMap();

	std::string objStrTexName = std::string();
	char objnamebuff[20], objTextureName[200];
	bool newObjectWindow = false;
	void renderNewObjectWindow();
	NewObjectInfo objinfo;

	bool newBGObjectWindow = false;
	void renderNewBGObjectWindow();

	void setUpBackgroundTexture();





};

#endif