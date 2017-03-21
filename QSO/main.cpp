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
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 200.0f);
	playerCamera.setView(vec3(0.0f, 0.0f, -10.0f)); // Adjust our Camera back by changing Z value
	
	// Testing Texture Manager
	TextureManager textureManager;
	textureManager.saveTexture("container.jpg", "container_1");
	textureManager.saveTexture("awesomeface.png", "awesomeface");
	textureManager.saveTextureMap("container2.png", "container_2"); // For diffusion Map
	textureManager.saveTextureMap("container2_specular.png", "container_specular"); // For specular Map
	textureManager.saveTextureMap("lava.jpg", "lava_2"); // For emission Map

	// Shader Programs <- Initialize program using selected ("vertex", "fragment") shaders

	Shader minShaderProgram("minVert.shader", "minFrag.shader"); // Simple Shader with color & texture, no Lighting effects
	Shader minLightingShaderProgram("minLightingVert.shader", "minLightingFrag.shader"); // Phong only
	Shader matLightingShaderProgram("matLightingVert.shader", "matLightingFrag.shader");  // Phong + Material (Color), no texture
	Shader lightingMapShaderProgram("lightingMapVert.shader", "lightingMapFrag.shader"); // Phong + Spec + Diffuse + Emission Map + HSV
	Shader simpleLightingMapShaderProgram("simpleLightingMapVert.shader", "simpleLightingMapFrag.shader"); // Phong + Spec + Diffuse Map
	Shader lampShaderProgram("lampVert.shader", "lampFrag.shader");  // Simple Lamp
	Shader directionalLightShaderProgram("directionalLightingVert.shader", "directionalLightingFrag.shader"); // Directional Light
	Shader attenuatedLightingShaderProgram("attenuatedLightingVert.shader", "attenuatedLightingFrag.shader"); // Attenuated Lighting
	Shader HSVShaderProgram("HSVVert.shader", "HSVFrag.shader"); // Only HSV with color

	// Testing Cube Renderer

	Transform cube1Pos;
	Transform lampPos; 
	Transform attenuatedObject0Pos;
	Transform attenuatedObject25Pos;
	Transform attenuatedObject50Pos;
	Transform attenuatedObject75Pos;
	Transform terrainPos;
	Transform sunPos;
	Material material;
	Material mapD;
	Material mapDS;
	Material mapDSE;
	Material mapE;
	

	// Material 1
	material.uv = "awesomeface";
	
	// Material with Diffuse Map
	mapD.diffuse = "container_2";
	
	// Material with Diffuse/Specular Map
	mapDS.diffuse = "container_2";
	mapDS.specular = "container_specular";

	// Material with Diff/Spec/Emi Map
	mapE.emission = "lava_2";

	// Material with Emission Map
	mapDSE.diffuse = "container_2";
	mapDSE.specular = "container_specular";
	mapDSE.emission = "lava_2";
	// Testing Terrain Triangle Strips

	Terrain terrain("terrain", 100, 100, 1.0f);
	terrain.init();
	Mesh terrainMesh = Mesh("terrain");
	mapData terrainData = terrain.getData();
	terrainMesh.mesh.vertices = (GLfloat*)terrainData.vertices;
	terrainMesh.mesh.indices = terrainData.indices;
	terrainMesh.mesh.normals = (GLfloat*)terrainData.normals;
	terrainMesh.mesh.indexCount = terrainData.indexCount;
	terrainMesh.mesh.vertexCount = terrainData.vertexCount;
	terrainMesh.mesh.mode = GL_TRIANGLE_STRIP;
	terrainMesh.generateMesh();

	//Mesh Objects

	// Lamps
	MeshRenderer testLampRenderer(material, &textureManager, &lampPos, &lampShaderProgram, &playerCamera);

	// Attenuated Objects
	MeshRenderer attenuatedObjectRenderer0(mapDSE, &textureManager, &attenuatedObject0Pos, &attenuatedLightingShaderProgram, &playerCamera);
	MeshRenderer attenuatedObjectRenderer25(mapDSE, &textureManager, &attenuatedObject25Pos, &attenuatedLightingShaderProgram, &playerCamera);
	MeshRenderer attenuatedObjectRenderer50(mapDSE, &textureManager, &attenuatedObject50Pos, &attenuatedLightingShaderProgram, &playerCamera);
	MeshRenderer attenuatedObjectRenderer75(mapDSE, &textureManager, &attenuatedObject75Pos, &attenuatedLightingShaderProgram, &playerCamera);
	
	// Terrain
	MeshRenderer terrainRenderer(mapE, &textureManager, &terrainPos, &attenuatedLightingShaderProgram, &playerCamera);

	// Create Polygons
	Polygon lamp;
	Cube attenuatedLight;

	// Init Polygons
	lamp.init();
	attenuatedLight.init();

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

	mat4 model;
	lampPos.translate(vec3(0.0f, 10.0f, 0.0f));
	lampPos.scale(3);
	lampPos.calculateModelMatrix();

	terrainPos.translate(vec3(-terrainData.xLength / 2, -5.0f, terrainData.zLength / 2));
	terrainPos.calculateModelMatrix();

	attenuatedObject0Pos.translate(vec3(0.0f, 0.0f, 0.0f));
	attenuatedObject0Pos.scale(3);
	attenuatedObject0Pos.calculateModelMatrix();

	attenuatedObject25Pos.translate(vec3(-25.0f, 5.0f, 0.0f));
	attenuatedObject25Pos.scale(3);
	attenuatedObject25Pos.calculateModelMatrix();

	attenuatedObject50Pos.translate(vec3(-50.0f, 5.0f, 0.0f));
	attenuatedObject50Pos.scale(3);
	attenuatedObject50Pos.calculateModelMatrix();

	attenuatedObject75Pos.translate(vec3(-75.0f, 5.0f, 0.0f));
	attenuatedObject75Pos.scale(3);
	attenuatedObject75Pos.calculateModelMatrix();

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

			//lampPos.rotate(45.0f*dt, vec3(0.0f, 1.0f, 0.0f), false);
			model = lampPos.calculateModelMatrix();


			//// End of Update

			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function

			testLampRenderer.renderObject(&lamp);

			attenuatedObjectRenderer0.renderObject(&attenuatedLight);
			attenuatedObjectRenderer25.renderObject(&attenuatedLight);
			attenuatedObjectRenderer50.renderObject(&attenuatedLight);
			attenuatedObjectRenderer75.renderObject(&attenuatedLight);

			terrainRenderer.renderObject(&terrainMesh);

			// End of Render

			graphicsHandler.end(); // Swaps scene buffers
			frameClock.resetClock(); // Once frame is done reset to 0
		}
	}
	MeshGenerator::destroy();
	graphicsHandler.destroy();

	return 0;
}
