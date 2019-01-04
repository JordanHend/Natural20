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


	struct nk_context *ctx;
	struct nk_colorf bg;
	~GUI();
private:
	//ref to map. It's editted from the GUI.
	Map * map;

	//for GM/Player layer tests. TODO: Add this.
	int defaultLayer = 0;
	bool showGMLayer = false;

	/*Tokens that are loaded to the map. Drag them from the token list onto the map to place
	TODO:::: Add empty token as a free token. Just place a blank token, and add details when its on the board. */
	std::vector<Token> tokens;

	//Rendering of menu bar + helpers.
	void renderMenuBar();


	//The bounds of the windows of the gui. Used so that you can't interact with the map while the mouse is hovering the gui.
	std::vector<Rect> bounds;

	//Basically hide stuff on main draw panel, so when you're dealing with something (like adding new map or token) you dont accidentally add more stuff.
	bool mainPanelInBackground = false;


	//Helpers and function to render window that processes a new map.
	bool newMapWindow = false;
	char mapnamebuff[20];
	char xbuff[6], ybuff[6];
	void renderNewMap();


	//Helpers and functions for rendering a window when adding a token to the list.
	std::string objStrTexName = std::string();
	char objnamebuff[20], objTextureName[200], objSize;
	bool newObjectWindow = false;
	void renderNewObjectWindow();
	

	//Helpers and functions for adding a background texture to the map
	bool newBGObjectWindow = false;
	void renderNewBGObjectWindow();
	void setUpBackgroundTexture();


	void drawObjectInfoWindow();





};

#endif