#pragma once

#include <glfw3.h>

#include "InputHandler.h"
#include "KeyboardInput.h"
#include "MouseInput.h"

class glfwInputHandler : public InputHandler
{
private:
	GLFWwindow *window;
	KeyboardInput *keyboardInput;
	MouseInput *mouseInput;
	bool exit = false;
	bool firstMouse = true;

public:
	glfwInputHandler();
	glfwInputHandler(GLFWwindow *window);
	virtual ~glfwInputHandler();

	bool keyPressed(int key);
	bool quitApplication();
	void setExit(bool exit);
	void pollEvent();
	void init();
	MouseInput *getMouse();
	KeyboardInput *getKeyboard();
};

