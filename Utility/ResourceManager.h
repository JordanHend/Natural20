
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glfw3.h>
#include <glad\glad.h>

#include "../Rendering/Texture2D.h"
#include "../Shader/Shader.h"


std::string SplitFilename(const std::string& str);

class ResourceManager
{
public:

	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture2D> Textures;
	
	static Shader   LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	static Shader   GetShader(std::string name);
	static bool		hasTexture(std::string name);
	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	static Texture2D GetTexture(std::string name);
	static void      Clear();
private:
	ResourceManager() { }
	static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif