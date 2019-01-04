#ifndef TEXTURERENDER_H
#define TEXTURERENDER_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Texture2D.h"
#include "../Shader\Shader.h"
extern float scale;
class TextureRenderer
{
public:
	TextureRenderer(Shader &shader)
	{
		this->shader = shader;
		this->initRenderData();
	};
	~TextureRenderer()
	{
		glDeleteVertexArrays(1, &this->quadVAO);
	};

	void DrawSprite(Texture2D &texture, glm::vec2 position,	glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	GLuint quadVAO;

	void initRenderData();
};

#endif