#include <iostream>

#include "Core.h"
#include "ShapeComponents.h"
#include "Physics.h"

#include "AudioComponent3D.h"

using namespace std;

glfwInputHandler inputHandler;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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
			cout << "key pressed " << key << endl;
		}
		else if (action == GLFW_RELEASE) {
			keyboard->setKey(key, false);
			cout << "key released" << endl;
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


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	MouseInput* mouse = inputHandler.getMouse();

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			mouse->setButtonPressed(0, true);
			printf("mouse click 0: \n");
		}
		else {
			mouse->setButtonPressed(0, false);
			printf("mouse release 0: \n");
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			mouse->setButtonPressed(1, true);
			printf("mouse click 1: \n");
		}
		else {
			mouse->setButtonPressed(1, false);
			printf("mouse release 1: \n");
		}
	}
}

int main(int argc, char *argv[]) {

	PhysicsWorld _world; //Initialize Physics
	_world.setGravity(vec3(0, -0.5, 0));
	glfwWindow *window = new glfwWindow(1920, 1080);
	openGLHandler graphicsHandler(window);

	graphicsHandler.init(); // Initialize Rendering Library

	inputHandler = glfwInputHandler(window->getWindow());
	
	// Set the required callback functions to register
	glfwSetKeyCallback(window->getWindow(), key_callback);
	glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
	glfwSetScrollCallback(window->getWindow(), scroll_callback);
	glfwSetMouseButtonCallback(window->getWindow(), mouse_button_callback);

	//GLFW Options
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Setup Camera

	Camera3rdPerson playerCamera ("camera", &inputHandler);
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 1000.0f);
	
	// Testing Texture Manager
	TextureManager *textureManager = TextureManager::instance();

	// Shader Programs <- Initialize program using selected ("vertex", "fragment") shaders

	Shader multiShadingProgram("multiLightVert.shader", "multiLightFrag.shader"); // For terrain: Advanced Shader with multiLight (Dir/Point/Spot light + Emission with HSV)
	Shader skyBoxShader("skyboxVert.shader", "skyboxFrag.shader"); // Basic shader for skybox, applies texture to cubemap. No lighting.
	Shader modelShader("modelVert.shader", "modelFrag.shader"); // Shader with multiLight (Dir/Point/Spot light) on models
	Shader HSVShader("HSVVert.shader", "HSVFrag.shader"); // Applies HSV and multiLight (Dir/Point/Spot light) on models/obj. 

	//Mesh Objects
	GLRenderer glRenderer;
	glRenderer.setCamera(&playerCamera);

	Skybox *skyBoxCube = new Skybox("skyBox");

	Terrain *terrain = new Terrain("terrain", 100, 100, 20.0f);

	Model *arissa = new Model("nanoSuit", "models/arissa/Arissa.dae");
	

	Material *material = new Material("BaseMaterial", multiShadingProgram);
	Material *multiMaterial = new Material("multiMaterial", modelShader);
	Material *multiMaterial2 = new Material("multiMaterial2", HSVShader);


	// UV's for Terrain
	material->addTexture("texture/dirt.png", DIFFUSE);
	material->addTexture("texture/path.png", SPECULAR);
	material->addTexture("lava.jpg", EMISSION);

	material->addTexture("texture/grassy.png", BACKGROUND_TEXTURE);
	material->addTexture("texture/dirt.png", R_TEXTURE);
	material->addTexture("texture/pinkFlowers.png", G_TEXTURE);
	material->addTexture("texture/path.png", B_TEXTURE);
	material->addTexture("texture/blendMap.png", BLEND_MAP);
	
	// UV's for Model (playerModel)
	multiMaterial->addTexture("container2.png", DIFFUSE);
	multiMaterial->addTexture("container2_specular.png", SPECULAR);
	multiMaterial->addTexture("lava.jpg", EMISSION);
	multiMaterial->addTexture("", NORMAL_MAP); // Need to include Normal Map from model here.

	// UV's for Model (Tree1)
	//multiMaterial2->addTexture("container2.png", DIFFUSE);
	//multiMaterial2->addTexture("container2_specular.png", SPECULAR);
	multiMaterial2->addTexture("lava.jpg", EMISSION);

	Material *skyboxMaterial = new Material("skyBox", skyBoxShader);
	skyboxMaterial->isCubMap = true;
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_rt.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_lf.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_up.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_dn.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_bk.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_ft.tga");

	//skyboxMaterial->cubeMaps.push_back("right.jpg");
	//skyboxMaterial->cubeMaps.push_back("left.jpg");
	//skyboxMaterial->cubeMaps.push_back("top.jpg");
	//skyboxMaterial->cubeMaps.push_back("bottom.jpg");
	//skyboxMaterial->cubeMaps.push_back("back.jpg");
	//skyboxMaterial->cubeMaps.push_back("front.jpg");

	Material *modelMat = new Material("modelMat", modelShader);
	GameObject *mushroom[20];

	btQuaternion quat = btQuaternion(btVector3(1.5f, 1.0f, 1.0f), glm::radians(-90.0f));
	for (int i = 0; i < 20; i++) {
		int px = rand() % 1000 - 500;
		int py = rand() % 10000;
		int pz = rand() % 1000 - 500;
		Model *modelTree = new Model("Tree1", "models/boletus/boletus_dae(collada)/boletus.dae");
		Material *multiMaterial3 = new Material("multiMaterial2", HSVShader);
		mushroom[i] = new GameObject("mushroom" + i);
		mushroom[i]->addComponent(modelTree);
		mushroom[i]->addComponent(multiMaterial3);
		mushroom[i]->addComponent(new RigidBody("shroomBody" + i, &_world, 10, vec3(px, py, pz), quat, true));
		mushroom[i]->addComponent(new AudioComponent3D("shroomAudio" + i, vec3(px, py, pz)));
		//mushroom[i]->getComponent<AudioComponent3D> //FIIIIIIX
		//mushroom[i]->init();
		mushroom[i]->transform.scale(1.0f);
	}

	GameObject *mountains[14];
	int numObstacles = 10; // Should be based on terrain boundary size. 
	for (int i = 0; i < numObstacles; i++) {
		int px = 50 + (25 * i);
		int py = 0;
		int pz = 50;
		Model *moutain = new Model("obstacle", "models/Rock1/Rock1.dae");
		Material *mountainMaterial = new Material("mountainMaterial", multiShadingProgram);
		mountains[i] = new GameObject("rocks" + i);
		mountains[i]->addComponent(moutain);
		mountains[i]->addComponent(mountainMaterial);
		mountains[i]->addComponent(new RigidBody("mountainBody" + i, &_world, 1, vec3(px, py, pz), true));
		mountains[i]->init();
		mountains[i]->transform.scale(10.0f);
	}

	//Model *borderObs = new Model("borderObstacle", "models/Rock1/Rock1.dae");
	//Material *mountainMaterial = new Material("borderObstacleMat", multiShadingProgram);
	//GameObject obstacle("rockObs");
	//obstacle.addComponent(borderObs);
	//obstacle.addComponent(mountainMaterial);
	//obstacle.addComponent(new RigidBody("rigidObs", &_world, 1, vec3(-10.0f, 0.0f, 900.0f), true));
	//obstacle.init();
	//obstacle.transform.scale(1000.0f, 25.0f, 10.0f);

	GameObject skyBox("skyBox");
	skyBox.addComponent(skyBoxCube);
	skyBox.addComponent(skyboxMaterial);

	GameObject playerModel("playerModel");
	playerModel.addComponent(arissa);
	playerModel.addComponent(modelMat);
	playerModel.addComponent(new PlayerMovement("playerMovement", &inputHandler, &playerCamera));
	playerModel.addComponent(new RigidBody("playerBody", &_world, 100, vec3(0,50,0), true));
	playerModel.getComponent<Movement>()->attachGameObject(&playerModel);
	playerModel.init();
	playerModel.transform.scale(0.1f);

	GameObject terrainOBJ("terrain");
	terrainOBJ.addComponent(terrain);
	terrainOBJ.addComponent(material);
	vec3 defaultState = vec3(-terrain->getData().xLength * 0.5f * terrain->getGridSize(), 0.0f, -terrain->getData().zLength * 0.5f * terrain->getGridSize());
	terrainOBJ.addComponent(new RigidBody("terrainBody", &_world, 0, vec3(defaultState.x, defaultState.y, defaultState.z)));
	terrainOBJ.init();
	//Sets Terrian to center
	terrainOBJ.getComponent<RigidBody>()->updateStep();
	terrainOBJ.transform.calculateModelMatrix();

	playerCamera.setObject(&playerModel);

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
		playerModel.getComponent<Movement>()->pollInputs(dt);

		//if (inputHandler.getKeyboard()->keyPressed(GLFW_KEY_L)) {
		//	playerCamera.setObject(&modelTree1);
		//	playerModel.getComponent<Movement>()->attachGameObject(&modelTree1);
		//}
		//else if (inputHandler.getKeyboard()->keyPressed(GLFW_KEY_K)){
		//	playerCamera.setObject(&playerModel);
		//	playerModel.getComponent<Movement>()->attachGameObject(&playerModel);
		//}

		_world.stepSimulation(dt, 10);

		//End of DeltaTime
		if (frameClock.alarm()) {

			// Process Inputs & Camera controls

			inputHandler.getMouse()->setLastPosition(inputHandler.getMouse()->getPosition());
			inputHandler.getMouse()->setLastScrollOffset(inputHandler.getMouse()->getScrollOffset());

			// End of Process Inputs

			//Audio Update
			//for (int i = 0; i < 20; i++) {
				//mushroom[i]->getComponent<AudioComponent3D>()->setSoundPosition(mushroom[i].transform.position)
				//mushroom[i]->getComponent<AudioComponent3D>()->setListenerPosition(playerModel.transform.position, playerModel.transform.rotation);
			//}

			// Update Function

			playerCamera.move();
			skyBox.transform.calculateModelMatrix();

			playerModel.transform.calculateModelMatrix();
			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function
			for (int i = 0; i < 20; i++) {
				glRenderer.renderObject(mushroom[i]);
			}

			for (int i = 0; i < numObstacles; i++) {
				glRenderer.renderObject(mountains[i]);
			}
			glRenderer.renderObject(&skyBox);
			glRenderer.renderObject(&playerModel);
			glRenderer.renderObject(&terrainOBJ);
			
			// End of Render

			graphicsHandler.end(); // Swaps scene buffers
			frameClock.resetClock(); // Once frame is done reset to 0
		}
	}

	// De-allocate Memory
	_world.destroy();
	MeshGenerator::destroy();
	TextureManager::instance()->destroy();
	GameObject::cleanUpObjects();
	graphicsHandler.destroy();
	

	return 0;
}
