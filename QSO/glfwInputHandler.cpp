#include "glfwInputHandler.h"



glfwInputHandler::glfwInputHandler()
{
}

glfwInputHandler::glfwInputHandler(GLFWwindow * window)
{
	glfwInputHandler::window = window;
	glfwInputHandler::keyboardInput = new KeyboardInput();
	glfwInputHandler::mouseInput = new MouseInput();
}

glfwInputHandler::~glfwInputHandler()
{
}

bool glfwInputHandler::keyPressed(int key)
{
	return glfwInputHandler::keyboardInput->keyPressed(key);
}

bool glfwInputHandler::quitApplication()
{
	return exit;
}

void glfwInputHandler::setExit(bool exit)
{
	glfwInputHandler::exit = exit;
}

void glfwInputHandler::pollEvent()
{
	glfwPollEvents();
}


void glfwInputHandler::init()
{
	
}

MouseInput *glfwInputHandler::getMouse()
{
	return glfwInputHandler::mouseInput;
}

KeyboardInput *glfwInputHandler::getKeyboard()
{
	return glfwInputHandler::keyboardInput;
}
