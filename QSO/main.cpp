#include <iostream>

#include "Shader.h"
#include "Window.h"
#include "glfwWindow.h"
#include "openGLHandler.h"
#include "Clock.h"
#include "TextureManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "CubeRenderer.h"

using namespace std;

int main(int argc, char *argv[]) {

	Window *window = new glfwWindow(800, 600);
	openGLHandler graphicsHandler(window);

	
	// Setup Camera

	Camera playerCamera;
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 100.0f);
	playerCamera.setView(vec3(0.0f, 0.0f, -10.0f)); // Adjust our Camera back by changing Z value

	graphicsHandler.init(); // Initialize Rendering Library
	
	// Testing Texture Manager
	TextureManager textureManager;
	
	textureManager.saveTexture("lava.jpg", "lava");

	// Testing Shaders
	Shader minShaderProgram("minVertex.shader", "minFrag.shader"); // Initialize minShader Programs using selected shaders.

	// Testing Cube Renderer

	Transform transform;
	Material material;
	material.texture = "lava";

	CubeRenderer cubeRenderer(material, &textureManager, &transform, &minShaderProgram, &playerCamera);
	cubeRenderer.init();

	// Set Frame Rate
	Clock frameClock;
	frameClock.startClock();
	frameClock.setDelay(1000.0f / 60.0f); //60 FPS

	double previousTime = 0.0f;
	double currentTime = 0.0f;

	// Testing Clock

	Clock clock;
	clock.startClock();

	// Game Loop
	bool flag = true;
	while (flag) {

		frameClock.updateClock(); // Ticks our Frame Clock
		clock.updateClock(); //Ticks App Clock

		// Calculates Delta Time
		
		currentTime = clock.getMilliseconds();
		double dt = (currentTime - previousTime) * 0.001f; //Convert DT to seconds

		//End of DeltaTime
		if (frameClock.alarm()) {
			printf("Delta Time: %d", dt);
			// Update Function
			// End of Update
			transform.translate(vec3(0,1*dt,0));
			transform.rotate(45.0f*dt, vec3(0, 1, 1), false);
			vec3 position = transform.getPosition();
			printf("%f,%f,%f\n", position.x, position.y, position.z);
			transform.calculateModelMatrix();
			
			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function
			cubeRenderer.renderObject();

			// End of Render

		graphicsHandler.end(); // Swaps scene buffers
		frameClock.resetClock(); // Once frame is done reset to 0
		previousTime = currentTime;
		}
	}

	graphicsHandler.destroy();

	return 0;
}