#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Window.h"
#include "glfwWindow.h"
#include "openGLHandler.h"
#include "Clock.h"
#include "TextureManager.h"
#include "Camera.h"
#include "GLRenderer.h"
#include "glfwInputHandler.h"
#include "Terrain.h"
#include "Mesh.h"
#include "Polygon.h"
#include "Cube.h"
#include "GameObject.h"
#include "Skybox.h"

using namespace std;

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
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 200.0f);
	playerCamera.setView(vec3(0.0f, 0.0f, -10.0f)); // Adjust our Camera back by changing Z value
	
	// Testing Texture Manager
	TextureManager *textureManager = TextureManager::instance();
	//textureManager.saveTexture("container.jpg", "container_1");
	//textureManager.saveTexture("awesomeface.png", "awesomeface");
	//textureManager.saveTextureMap("container2.png", "container_2"); // For diffusion Map
	//textureManager.saveTextureMap("container2_specular.png", "container_specular"); // For specular Map
	//textureManager.saveTextureMap("lava.jpg", "lava_2"); // For emission Map

	// Shader Programs <- Initialize program using selected ("vertex", "fragment") shaders

	Shader ShaderProgram("lightingMapVert.shader", "lightingMapFrag.shader");
	Shader skyBoxShader("skyboxVert.shader", "skyboxFrag.shader");

	//Mesh Objects
	GLRenderer glRenderer;
	glRenderer.setCamera(&playerCamera);

	Cube *cube1 = new Cube("Cube");
	Skybox *skyBoxCube = new Skybox("skyBox");
	Material *material = new Material("BaseMaterial", ShaderProgram);
	material->diffuseMap = "container2.png";
	material->specularMap = "container2_specular.png";
	material->emissionMap = "lava.jpg";
	
	Material *skyboxMaterial = new Material("skyBox", skyBoxShader);
	skyboxMaterial->isCubMap = true;
	skyboxMaterial->cubeMaps.push_back("right.jpg");
	skyboxMaterial->cubeMaps.push_back("left.jpg");
	skyboxMaterial->cubeMaps.push_back("top.jpg");
	skyboxMaterial->cubeMaps.push_back("bottom.jpg");
	skyboxMaterial->cubeMaps.push_back("back.jpg");
	skyboxMaterial->cubeMaps.push_back("front.jpg");
	
	GameObject cube("cube");
	cube.addComponent(cube1);
	cube.addComponent(material);

	GameObject skyBox("skyBox");
	skyBox.addComponent(skyBoxCube);
	skyBox.addComponent(skyboxMaterial);


	// Create Polygons
	
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

	// Initial Polygon Position, size and rotation

	/* 
	Use to debug position of polygon:

	vec3 position = lampPos.getPosition();
	printf("%f,%f,%f\n", position.x, position.y, position.z);

	*/

	cube.transform.translate(vec3(0.0f, 6.0f, 0.0f));
	cube.transform.scale(vec3(1));

	// Game Loop
	while (!inputHandler.quitApplication()) {

		//Checks and calls events
		inputHandler.pollEvent();

		frameClock.updateClock(); // Ticks our Frame Clock
		clock.updateClock(); //Ticks App Clock

		// Calculates Delta Time
		previousTime = currentTime;
		currentTime = clock.getMilliseconds();
		double dt = (currentTime - previousTime) * 0.01f; //Convert DT to seconds

		//End of DeltaTime
		if (frameClock.alarm()) {

			// Process Inputs & Camera controls

			playerCamera.processMouseScroll(*inputHandler.getMouse(), dt);
			playerCamera.processCameraMouseMovement(*inputHandler.getMouse(), dt);
			playerCamera.processKeyBoard(*inputHandler.getKeyboard(), dt);
			
			playerCamera.GetViewMatrix();
			inputHandler.getMouse()->setLastPosition(inputHandler.getMouse()->getPosition());
			inputHandler.getMouse()->setLastScrollOffset(inputHandler.getMouse()->getScrollOffset());

			// End of Process Inputs

			// Update Function
			skyBox.transform.calculateModelMatrix();
			cube.transform.calculateModelMatrix();
			

			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function
			glRenderer.renderObject(skyBox.getComponent<Shape>(), skyBox.transform, skyBox.getComponent<Material>());
			glRenderer.renderObject(cube.getComponent<Shape>(), cube.transform, cube.getComponent<Material>());
			
			
			// End of Render

			graphicsHandler.end(); // Swaps scene buffers
			frameClock.resetClock(); // Once frame is done reset to 0
		}
	}
	MeshGenerator::destroy();
	TextureManager::instance()->destroy();
	cube.destroy();
	graphicsHandler.destroy();

	return 0;
}
