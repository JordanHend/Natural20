#ifndef FONT_GL_H
#define FONT_GL_H
#include "ResourceManager.h"
#include <glfw3.h>
#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H 

extern int SCREEN_WIDTH, SCREEN_HEIGHT;

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Font
{
public:

	Font()
	{

	};
	Font(std::string fontDirectory);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	
	~Font();

private:
	GLuint VAO;
	GLuint VBO;
	Shader shader;
	std::map<GLchar, Character> Characters;
};

#endif