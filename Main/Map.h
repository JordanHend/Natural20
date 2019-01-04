#ifndef DND_MAP_H
#define DND_MAP_H

#include "../Utility/Camera.h"
#include "../Utility/ResourceManager.h"
#include "../Rendering/TextureRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../Utility/Rect.h"
#include "../Utility/Font.h"


struct Object
{
	std::string name;
	Texture2D tex;
	Rect rect;
	glm::vec2 pos = glm::vec3(-1);
	glm::vec2 rotation;
	float scale = 1;
};

struct BackgroundObject
{
	Texture2D tex;
	Rect rect;
	glm::vec2 pos;
};

///* Again, I know its bad practice to extern but LMAO i didnt feel like hassling with passing references for all this stuff and setting it up.

//Screen dimentions. Editted by framebuffer callback.
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//The projecction matrix, also editted when window resized.
extern glm::mat4 projection;

//Camera of scene
extern Camera camera;

//OVERALL scale of everything on the map. Editted by scroll callback in main.cpp
extern float scale;

//Font of scene. For rendering X next to objects that are on map.
extern Font dFont;

//Ref to window
extern GLFWwindow * window;

//For mouse calculations, for collision detection, etc.
extern float lastX;
extern float lastY;
extern bool mButtonDown;


typedef Object Token;
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
	//Tokens from gui.
	std::vector<Token> * tokens;
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

	//Is the map ready to render
	bool readyToDraw()
	{
		return !(bounds.x == 0 || bounds.y == 0);
	};

	//Draws the grid (if it's toggled on) and the map
	void draw();

	//Handle mouse input on map.
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
	
	//The size of the map in BLOCKS (5 ft blocks)
	glm::ivec2 bounds = glm::ivec2(0,0);

	//flag & image for rendering the background.
	bool bginitialized = false;
	Texture2D BGIMAGE;

	//Ptr to renderer
	TextureRenderer * renderer;
	

	//The collision area of each square of grid. Used for collision detection.
	std::vector<Rect> logicalGrid;


	//Name of map.
	std::string name;

	//flag for drawing the grid.
	bool shouldDrawGrid = true;

	//Buffers for grid to GPU
	unsigned int gridVBO, gridVAO, numLines;

	//flag for deleting the grid buffers when calling init
	bool gridSetup = false;
	//Delete grid buffers.
	void deleteGrid();
	//Draw grid. called in public draw function.
	void drawGrid();
	
	
};

#endif