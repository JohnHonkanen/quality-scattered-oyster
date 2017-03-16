#include <iostream>

#include "Shader.h"
#include "Window.h"
#include "glfwWindow.h"
#include "openGLHandler.h"
#include "Clock.h"
#include "TextureManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "glfwInputHandler.h"
#include "Terrain.h"
#include "Mesh.h"

using namespace std;

struct cube {
	Mesh mesh[6];

};

glfwInputHandler inputHandler;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	MouseInput* mouse = inputHandler.getMouse();
	mouse->setScrollOffset(vec2(xoffset, yoffset));
}


//Closing the application
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	KeyboardInput* keyboard = inputHandler.getKeyboard();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		inputHandler.setExit(true);
		cout << "Exit Pressed" << endl;
	}
		
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) {
			keyboard->setKey(key, true);
			//cout << "key pressed" << endl;
		}
		else if (action == GLFW_RELEASE) {
			keyboard->setKey(key, false);
			//cout << "key released" << endl;
		}
			
	}
}

// Mouse control

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	
	//Check if this is the first time receiving the mouse input and if so, we first update the initial mouse position
	// to the new xpos and ypos values; the resuling mouse movement will then use the entered mouse's position
	// coordinates to calculate it's offset. - Helps avoid large offsets and movement jump when mouse enters the 
	// program display for the first time. 
	MouseInput* mouse = inputHandler.getMouse();
	if (firstMouse) {
		mouse->setPosition(vec2(xpos, ypos));
		firstMouse = false;
	}
	//Calcualate the offset movement between the last and current frames.
	vec2 mousePosition = mouse->getPosition();
	GLfloat xOffset = xpos - mousePosition.x;
	GLfloat yOffset = mousePosition.y - ypos; //Reverse since y-coordinates go from bottom to left
	mouse->setOffset(vec2(xOffset, yOffset));
	mouse->setPosition(vec2(xpos, ypos));
}

int main(int argc, char *argv[]) {

	glfwWindow *window = new glfwWindow(800, 600);
	openGLHandler graphicsHandler(window);

	graphicsHandler.init(); // Initialize Rendering Library

	inputHandler = glfwInputHandler(window->getWindow());
	
	// Set the required callback functions to register
	glfwSetKeyCallback(window->getWindow(), key_callback);
	glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
	glfwSetScrollCallback(window->getWindow(), scroll_callback);

	//GLFW Options
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Setup Camera

	Camera playerCamera (vec3(0,0,10.0f), vec3(0,1,0), 0.0f, 0.0f);
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 100.0f);
	playerCamera.setView(vec3(0.0f, 0.0f, -10.0f)); // Adjust our Camera back by changing Z value
	
	// Testing Texture Manager
	TextureManager textureManager;
	
	textureManager.saveTexture("lava.jpg", "lava");

	// Testing Shaders
	Shader minShaderProgram("minVertex.shader", "minFrag.shader"); // Initialize minShader Programs using selected shaders.

	// Testing Cube Renderer

	Transform transform;
	Material material;
	material.texture = "lava";
	Mesh cube("Cube");
	cube.mesh.vertexCount = 8;
	cube.mesh.indexCount = 36;
	cube.mesh.vertices = new GLfloat[cube.mesh.vertexCount * 3]{
		
		//Front Face
		-0.5f, -0.5f, 0.5f,  // 0
		 0.5f, -0.5f, 0.5f,  // 1
		 0.5f, 0.5f, 0.5f,   // 2
		-0.5f, 0.5f, 0.5f,   // 3

		//Back Face
		-0.5f, -0.5f, -0.5f, // 4
		 0.5f, -0.5f, -0.5f, // 5
		 0.5f, 0.5f, -0.5f,  // 6
		-0.5f, 0.5f, -0.5f   // 7
	};

	cube.mesh.indices = new GLuint[cube.mesh.indexCount]{
		
			//front
			0, 1, 2,
			2, 3, 0,

			//top
			1, 5, 6,
			6, 2, 1,

			// back
			7, 6, 5,
			5, 4, 7,

			// bottom
			4, 0, 3,
			3, 7, 4,

			// left
			4, 5, 1,
			1, 0, 4,

			// right
			3, 2, 6,
			6, 7, 3,
	};

	cube.mesh.uv = new GLfloat[cube.mesh.vertexCount * 2]{
		
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
		
		
		
	};

	cube.generateMesh();
	MeshRenderer MeshRenderer(&cube, material, &textureManager, &transform, &minShaderProgram, &playerCamera);

	// Set Frame Rate
	Clock frameClock;
	frameClock.startClock();
	frameClock.setDelay(1000.0f / 60.0f); //60 FPS

	double previousTime = 0.0f;
	double currentTime = 0.0f;

	// Testing Clock

	Clock clock;
	clock.startClock();

	KeyboardInput* keyboard = inputHandler.getKeyboard();

	// Game Loop
	while (!inputHandler.quitApplication()) {

		//Checks and calls events
		inputHandler.pollEvent();

		frameClock.updateClock(); // Ticks our Frame Clock
		clock.updateClock(); //Ticks App Clock

		// Calculates Delta Time
		
		currentTime = clock.getMilliseconds();
		double dt = (currentTime - previousTime) * 0.001f; //Convert DT to seconds

		//End of DeltaTime
		if (frameClock.alarm()) {

			// Process Inputs & Camera controls

			playerCamera.processMouseScroll(*inputHandler.getMouse(), dt);
			playerCamera.processCameraMouseMovement(*inputHandler.getMouse(), dt);
			playerCamera.processKeyBoard(*inputHandler.getKeyboard(), dt);
			
			playerCamera.GetViewMatrix();
			inputHandler.getMouse()->setLastPosition(inputHandler.getMouse()->getPosition());

			// End of Process Inputs

			// Update Function
			
			//transform.translate(vec3(0, 1 * dt, 0));
			transform.rotate(45.0f*dt, vec3(0, 1, 1), false);
			mat4 model = transform.calculateModelMatrix();

			//// End of Update
			//transform.translate(vec3(0,1*dt,0));
			//transform.rotate(45.0f*dt, vec3(0, 1, 1), false);
			//vec3 position = transform.getPosition();
			//printf("%f,%f,%f\n", position.x, position.y, position.z);
			//transform.calculateModelMatrix();
			
			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function
			MeshRenderer.renderObject();

			//MeshRenderer2.renderObject();

			// End of Render

		graphicsHandler.end(); // Swaps scene buffers
		frameClock.resetClock(); // Once frame is done reset to 0
		previousTime = currentTime;
		}
	}

	graphicsHandler.destroy();

	return 0;
}
