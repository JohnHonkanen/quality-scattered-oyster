#include <iostream>

#include "Shader.h"
#include "Window.h"
#include "glfwWindow.h"
#include "openGLHandler.h"
#include "Clock.h"
#include "TextureManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"

using namespace std;

int main(int argc, char *argv[]) {

	Window *window = new glfwWindow(800, 600);
	openGLHandler graphicsHandler(window);

	
	// Setup Camera

	Camera playerCamera;
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 100.0f);
	playerCamera.setView(vec3(0.0f, 0.0f, -10.0f)); // Adjust our Camera back by changing Z value

	graphicsHandler.init(); // Initialize Rendering Library
	
	TextureManager textureManager;
	
	textureManager.saveTexture("lava.jpg", "lava");

	// Testing Shaders
	Shader minShaderProgram("minVertex.shader", "minFrag.shader"); // Initialize minShader Programs using selected shaders.

	// Set Frame Rate
	Clock frameClock;
	frameClock.startClock();
	frameClock.setDelay(1000.0f / 60.0f); //60 FPS

	double previousTime = 0.0f;
	double currentTime = 0.0f;

	// Testing Clock

	Clock clock;
	clock.startClock();
	clock.setDelayInSeconds(2);
 
	while (!clock.alarm()) {
		clock.updateClock();
		cout << clock.getSeconds() << endl;
	}

	//Testing Sprite Renderer & Textures
	Transform transform = Transform();

	SpriteRenderer spriteRenderer("lava.jpg", "lava", &textureManager, &transform, &minShaderProgram);
	spriteRenderer.init();

	// Game Loop
	bool flag = true;
	while (flag) {

		graphicsHandler.start(); // Sets up rendering loop

		spriteRenderer.renderObject();

		graphicsHandler.end(); // Swaps scene buffers

	}

	

	cin.get();

	graphicsHandler.destroy();

	return 0;
}