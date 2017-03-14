#include <iostream>

#include "Shader.h"
#include "Window.h"
#include "glfwWindow.h"
#include "openGLHandler.h"
#include "Clock.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	Window *window = new glfwWindow(800, 600);
	openGLHandler graphicsHandler(window);

	graphicsHandler.init(); // Initialize Rendering Library
	
	graphicsHandler.start();
	graphicsHandler.end();

	cin.get();

	graphicsHandler.destroy();

	return 0;
}