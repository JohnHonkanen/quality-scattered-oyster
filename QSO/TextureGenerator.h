#pragma once

#include <GL\glew.h>
#include <IL\il.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TextureGenerator
{
public:
	TextureGenerator();
	virtual ~TextureGenerator();

	static GLuint createTexture(const string fileLocation);
	static GLuint createTextureMap(const string fileLocation, GLint min, GLint max);
	static GLuint createCubeMap(const vector<string> faces);
};

