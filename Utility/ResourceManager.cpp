#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../Includes\stb_image.h"

std::string SplitFilename(const std::string& str)
{
	std::size_t found = str.find_last_of("/\\");
	return(str.substr(found + 1));
}

std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;


Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

bool ResourceManager::hasTexture(std::string name)
{

	std::map<std::string, Texture2D>::iterator it = ResourceManager::Textures.find(name);
	if (it != ResourceManager::Textures.end())
	{
		return true;
	}
	return false;
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::Clear()
{
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	Shader shader;
	if(gShaderFile == nullptr)
	shader.init(vShaderFile, fShaderFile);
	else
	shader.init(vShaderFile,gShaderFile,fShaderFile);

	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	int width, height, nrComponents;


	unsigned char *image = stbi_load(file, &width, &height, &nrComponents, 0);
	if (image)
	{
	
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = format;
		texture.Generate(width, height, image);
		stbi_image_free(image);
	}
	else
	{
		std::cout << "Failed to load texture at " << file << "!\n"; 
	}
	return texture;
}