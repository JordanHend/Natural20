#ifndef DND_MAP_H
#define DND_MAP_H

#include "Camera.h"
#include "ResourceManager.h"
#include "TextureRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Rect.h"
#include "Font.h"
extern glm::mat4 projection;
extern Camera camera;
extern float scale;
extern Font dFont;

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
typedef Object Token;
extern GLFWwindow * window;
extern float lastX;
extern float lastY;
extern bool mButtonDown;

class Map
{
public:
	//If you select object on the board, this points to it.
	Object * selBoardObject = NULL;

	//The token being grabbed from the gui. When released lmb, checks for where on board to put it.
	Token * selected_token = NULL;

	//Normal Object (visible to players)
	std::vector<Object> objects;
	//Not visible to players
	std::vector<Object> GMObjects;

	std::vector<BackgroundObject> backgroundObjects;
	Texture2D background;

	Map()
	{

	};
	
	Map(glm::ivec2 dimen, TextureRenderer * rend = NULL)
	{
		this->bounds = dimen;
		init(bounds, rend);
	}

	void init(glm::ivec2 bounds, TextureRenderer * rend = NULL);


	void setBGTexture(Texture2D tex)
	{
		bginitialized = true;
		this->BGIMAGE = tex;
	}
	glm::ivec2 getMapBounds()
	{
		return bounds;
	};



	void setRenderer(TextureRenderer * rend)
	{
		this->renderer = rend;
	}

	bool readyToDraw()
	{
		return !(bounds.x == 0 || bounds.y == 0);
	};
	void draw();
	void logic();

	bool getGridRender()
	{
		return shouldDrawGrid;
	}
	void setGridRender(bool value)
	{
		shouldDrawGrid = value;
	}

	void setName(std::string name)
	{
		this->name = name;
	}
	std::string getName()
	{
		return name;
	}

	
	~Map();

private:
	
	glm::ivec2 bounds = glm::ivec2(0,0);
	bool bginitialized = false;
	Texture2D BGIMAGE;
	TextureRenderer * renderer;
	
	std::vector<Rect> logicalGrid;

	std::string name;
	bool shouldDrawGrid = true;
	unsigned int gridVBO, gridVAO, numLines;
	bool gridSetup = false;
	void deleteGrid();
	void drawGrid();
	
	
};

#endif