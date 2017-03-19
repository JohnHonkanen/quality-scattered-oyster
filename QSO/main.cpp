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
#include "Polygon.h"
#include "Cube.h"

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
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 100.0f);
	playerCamera.setView(vec3(0.0f, 0.0f, -10.0f)); // Adjust our Camera back by changing Z value
	
	// Testing Texture Manager
	TextureManager textureManager;
	textureManager.saveTexture("container.jpg", "container_1");
	textureManager.saveTexture("awesomeface.png", "awesomeface");
	textureManager.saveTextureMap("container2.png", "container_2"); // For diffusion Map
	textureManager.saveTextureMap("container2_specular.png", "container_specular"); // For specular Map
	textureManager.saveTextureMap("lava.jpg", "lava_2"); // For emission Map

	// Shader Programs <- Initialize program using selected ("vertex", "fragment") shaders

	Shader minShaderProgram("minVert.shader", "minFrag.shader");
	Shader minLightingShaderProgram("minLightingVert.shader", "minLightingFrag.shader");
	Shader matLightingShaderProgram("matLightingVert.shader", "matLightingFrag.shader");
	Shader lightingMapShaderProgram("lightingMapVert.shader", "lightingMapFrag.shader");
	Shader simpleLightingMapShaderProgram("simpleLightingMapVert.shader", "simpleLightingMapFrag.shader");
	Shader lampShaderProgram("lampVert.shader", "lampFrag.shader"); 

	// Testing Cube Renderer

	Transform cube1Pos;
	Transform cube2Pos;
	Transform cube3Pos;
	Transform cube4Pos;
	Transform cube5Pos;
	Transform cube6Pos;
	Transform cube7Pos;
	Transform cube8Pos;
	Transform lampPos; 
	Material material;
	Material mapD;
	Material mapDS;
	Material mapDSE;
	Material mapE;

	// Material 1
	material.uv = "container_1";
	
	// Material with Diffuse Map
	mapD.diffuse = "container_2";

	// Material with Diffuse/Specular Map
	mapDS.diffuse = "container_2";
	mapDS.specular = "cotainer_specular";

	// Material with Diff/Spec/Emi Map
	mapE.emission = "lava_2";

	// Material with Emission Map
	mapDSE.diffuse = "container_2";
	mapDSE.specular = "cotainer_specular";
	mapDSE.emission = "lava_2";

	

	//Mesh Objects
	MeshRenderer MeshRenderer1(material, &textureManager, &cube1Pos, &minShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer2(material, &textureManager, &cube2Pos, &minLightingShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer3(material, &textureManager, &lampPos, &lampShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer4(material, &textureManager, &cube3Pos, &minLightingShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer5(material, &textureManager, &cube4Pos, &matLightingShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer6(mapD, &textureManager, &cube5Pos, &lightingMapShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer7(mapDS, &textureManager, &cube6Pos, &simpleLightingMapShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer8(mapE, &textureManager, &cube7Pos, &lightingMapShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer9(mapDSE, &textureManager, &cube8Pos, &lightingMapShaderProgram, &playerCamera);

	// Create Polygons
	Polygon cube1;
	Polygon cube2;
	Cube cube3;
	Cube cube4;
	Cube cube5;
	Cube cube6;
	Cube cube7;
	Cube cube8;
	Polygon lamp;

	// Init Polygons
	cube1.init();
	cube2.init();
	cube3.init();
	cube4.init();
	cube5.init();
	cube6.init();
	cube7.init();
	cube8.init();
	lamp.init();

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

	mat4 model;
	lampPos.translate(vec3(0.0f, 10.0f, 0.0f));
	lampPos.calculateModelMatrix();

	cube1Pos.translate(vec3(-6.0f, 0.0f, 0.0f));
	cube1Pos.scale(vec3(3));

	cube2Pos.translate(vec3(5.0f, 0.0f, 0.0f));
	cube2Pos.scale(vec3(1));

	cube3Pos.translate(vec3(35.0f, 0.0f, 0.0f));
	cube3Pos.scale(vec3(8));

	cube4Pos.translate(vec3(15.0f, 0.0f, 20.0f));
	cube4Pos.scale(vec3(8));

	cube5Pos.translate(vec3(15.0f, 0.0f, -20.0f));
	cube5Pos.scale(vec3(8));

	cube6Pos.translate(vec3(5.0f, 0.0f, -20.0f));
	cube6Pos.scale(vec3(8));
	model = cube6Pos.calculateModelMatrix();

	cube7Pos.translate(vec3(-5.0f, 0.0f, -20.0f));
	cube7Pos.scale(vec3(8));
	model = cube7Pos.calculateModelMatrix();

	cube8Pos.translate(vec3(-15.0f, 0.0f, -20.0f));
	cube8Pos.scale(vec3(8));
	model = cube8Pos.calculateModelMatrix();
	

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
			
			//cube1Pos.rotate(45.0f*dt, vec3(0, 1, 0), false);
			model = cube1Pos.calculateModelMatrix();

			cube2Pos.rotate(-45.0f*dt, vec3(0, 1, 0), false);
			model = cube2Pos.calculateModelMatrix();

			//lampPos.rotate(45.0f*dt, vec3(0.0f, 1.0f, 0.0f), false);
			model = lampPos.calculateModelMatrix();

			cube3Pos.rotate(-45.0f*dt, vec3(0, 1, 0), false);
			model = cube3Pos.calculateModelMatrix();
			//// End of Update
			
			cube4Pos.rotate(-45.0f*dt, vec3(0, 1, 0), false);
			model = cube4Pos.calculateModelMatrix();

			cube5Pos.rotate(-45.0f*dt, vec3(0, 1, 0), false);
			model = cube5Pos.calculateModelMatrix();

			


			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function
			MeshRenderer1.renderObject(&cube1); 
			MeshRenderer2.renderObject(&cube2);
			MeshRenderer3.renderObject(&lamp);
			MeshRenderer4.renderObject(&cube3);
			MeshRenderer5.renderObject(&cube4);
			MeshRenderer6.renderObject(&cube5);
			MeshRenderer7.renderObject(&cube6);
			MeshRenderer8.renderObject(&cube7);
			MeshRenderer9.renderObject(&cube8);


			//MeshRenderer2.renderObject(&cube);

			// End of Render

		graphicsHandler.end(); // Swaps scene buffers
		frameClock.resetClock(); // Once frame is done reset to 0
		}
	}
	MeshGenerator::destroy();
	graphicsHandler.destroy();

	return 0;
}
