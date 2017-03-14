#pragma once

#include <iostream>

#include "Window.h" //Include Window before glfw.
#include <glfw3.h>

using namespace std;

class glfwWindow : public Window
{
private:
	GLFWwindow *window;

public:
	glfwWindow(GLuint screenWIDTH, GLuint screenHEIGHT);
	virtual ~glfwWindow();

	void init();
	void swapBuffers();
	void destroy();

};

