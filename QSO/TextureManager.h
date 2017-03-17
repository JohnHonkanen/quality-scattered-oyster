#pragma once

#include <GL\glew.h>
#include <map>
#include <string>

#include "TextureGenerator.h"

using namespace std;

class TextureManager
{
private:
	map<string, GLuint> textures;

public:
	TextureManager();
	virtual ~TextureManager();

	void saveTexture(const string fileLocation, const string textureName);
	void saveTextureMap(const string fileLocation, const string textureName, GLint min = GL_LINEAR_MIPMAP_LINEAR, GLint max = GL_NEAREST_MIPMAP_NEAREST);
	void deleteTexture(const string textureName);
	void destroy();

	GLuint getTexture(const string textureName);

};

