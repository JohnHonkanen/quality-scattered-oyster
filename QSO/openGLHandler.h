#pragma once

#include <GL\glew.h>
#include <IL\il.h>
#include <iostream>
#include "GraphicsHandler.h"
#include "Window.h"
#include "Transform.h"

using namespace std;

class openGLHandler: public GraphicsHandler // GraphicsHandler = Renderer
{
private:
	Window *window;
	Transform view;
	Transform projection;

public:
	openGLHandler(Window *window);
	virtual ~openGLHandler();

	void init();
	void start();
	void end();
	void destroy();
};

