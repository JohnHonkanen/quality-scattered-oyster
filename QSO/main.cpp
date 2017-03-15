#include <iostream>

#include "Shader.h"
#include "Window.h"
#include "glfwWindow.h"
#include "openGLHandler.h"
#include "Clock.h"
#include "TextureManager.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	Window *window = new glfwWindow(800, 600);
	openGLHandler graphicsHandler(window);

	graphicsHandler.init(); // Initialize Rendering Library
	
	TextureManager textureManager;
	
	textureManager.saveTexture("lava.png", "lava");

	// Testing Shaders
	Shader minShaderProgram("minFrag.shader", "minVertex.shader"); // Initialize minShader Programs using selected shaders.

	// Set Frame Rate
	Clock frameClock;
	frameClock.startClock();
	frameClock.setDelay(1000.0f / 60.0f); //60 FPS

	double previousTime = 0.0f;
	double currentTime = 0.0f;

	// Testing Clock

	Clock clock;
	clock.startClock();
	clock.setDelayInSeconds(5);

	while (!clock.alarm()) {
		clock.updateClock();
		cout << clock.getSeconds() << endl;
	}

	
	// Game Loop
	bool flag = true;
	while (flag) {

		graphicsHandler.start(); // Sets up rendering loop


		graphicsHandler.end(); // Swaps scene buffers

	}

	

	cin.get();

	graphicsHandler.destroy();

	return 0;
}