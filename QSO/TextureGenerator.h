#pragma once

#include <GL\glew.h>
#include <IL\il.h>

#include <iostream>
#include <string>

using namespace std;

class TextureGenerator
{
public:
	TextureGenerator();
	virtual ~TextureGenerator();

	static GLuint createTexture(const string fileLocation);
};

