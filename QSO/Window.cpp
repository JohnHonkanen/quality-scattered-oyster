#include "Window.h"

GLuint Window::screenWIDTH;
GLuint Window::screenHEIGHT;

Window::Window(GLuint screenWIDTH, GLuint screenHEIGHT)
{
	Window::screenWIDTH = screenWIDTH;
	Window::screenHEIGHT = screenHEIGHT;
}

Window::~Window()
{
}
