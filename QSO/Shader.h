#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GL\glew.h"
#include <glfw3.h>

using namespace std;

class Shader
{
public:
	GLuint program;
	Shader(const char *vertexPath, const char *fragmentPath); // Find, Initialize, Logs and Checks Shader for error
	void Use();
};

#endif