#pragma once

#include <GL\glew.h>

class Window
{
public:
	Window(GLuint screenWIDTH, GLuint screenHEIGHT);
	virtual ~Window();
	virtual void init() = 0;
	virtual void swapBuffers() = 0;
	virtual void destroy() = 0;

	static GLuint screenWIDTH, screenHEIGHT;
};

