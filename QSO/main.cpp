#include <iostream>
#include <time.h>
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

	srand(time(NULL));

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

	Shader multiShadingProgram("shaders/multiLightVert.shader", "shaders/multiLightFrag.shader"); // For terrain: Advanced Shader with multiLight (Dir/Point/Spot light + Emission with HSV)
	Shader skyBoxShader("shaders/skyboxVert.shader", "shaders/skyboxFrag.shader"); // Basic shader for skybox, applies texture to cubemap. No lighting.
	Shader modelShader("shaders/modelVert.shader", "shaders/modelFrag.shader"); // Shader with multiLight (Dir/Point/Spot light) on models
	Shader HSVShader("shaders/HSVVert.shader", "shaders/HSVFrag.shader"); // Applies HSV and multiLight (Dir/Point/Spot light) on models/obj. 

	//Mesh Objects
	GLRenderer glRenderer;
	glRenderer.setCamera(&playerCamera);

	Skybox *skyBoxCube = new Skybox("skyBox");

	Terrain *terrain = new Terrain("terrain", 50, 50, 40.0f);

	Model *arissa = new Model("nanoSuit", "models/arissa/Arissa.dae");
	

	Material *material = new Material("BaseMaterial", multiShadingProgram);
	Material *multiMaterial = new Material("multiMaterial", modelShader);
	Material *multiMaterial2 = new Material("multiMaterial2", HSVShader);


	// UV's for Terrain
	material->addTexture("texture/dirt.png", DIFFUSE);
	material->addTexture("texture/path.png", SPECULAR);
	material->addTexture("texture/lava.jpg", EMISSION);

	material->addTexture("texture/grassy.png", BACKGROUND_TEXTURE);
	material->addTexture("texture/dirt.png", R_TEXTURE);
	material->addTexture("texture/pinkFlowers.png", G_TEXTURE);
	material->addTexture("texture/path.png", B_TEXTURE);
	material->addTexture("texture/blendMap.png", BLEND_MAP);
	
	// UV's for Model (playerModel)
	multiMaterial->addTexture("texture/container2.png", DIFFUSE);
	multiMaterial->addTexture("texture/container2_specular.png", SPECULAR);
	multiMaterial->addTexture("texture/lava.jpg", EMISSION);
	multiMaterial->addTexture("", NORMAL_MAP); // Need to include Normal Map from model here.

	// UV's for Model (Tree1)
	multiMaterial2->addTexture("texture/lava.jpg", EMISSION);

	Material *skyboxMaterial = new Material("skyBox", skyBoxShader);
	skyboxMaterial->isCubMap = true;
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_rt.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_lf.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_up.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_dn.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_bk.tga");
	skyboxMaterial->cubeMaps.push_back("skybox/ame_nebula/purplenebula_ft.tga");


	Material *modelMat = new Material("modelMat", modelShader);
	const int bigMushroom = 5;
	GameObject *mushroom[bigMushroom];

	AudioComponent2D background("background");
	background.setVolume(0.6f);
	background.playMusic("audio/music/night.wav");

	btQuaternion quat = btQuaternion(btVector3(1.5f, 1.0f, 1.0f), glm::radians(-90.0f));
	for (int i = 0; i < bigMushroom; i++) {
		int px = rand() % 1500 - 750;
		int py = rand() % 100;
		int pz = rand() % 1500 - 750;
		Model *modelTree = new Model("Tree1", "models/boletus/boletus_dae(collada)/boletus.dae");
		Material *multiMaterial3 = new Material("multiMaterial2", modelShader);
		mushroom[i] = new GameObject("mushroom" + i);
		mushroom[i]->TerrainOffset = vec3(0, -5, 0);
		mushroom[i]->addComponent(modelTree);
		mushroom[i]->addComponent(multiMaterial3);
		mushroom[i]->addComponent(new RigidBody("shroomBody" + i, &_world, 10, vec3(px, py, pz), quat, true));
		mushroom[i]->addComponent(new CollisionObject(vec3(15.0f, 5.0f, 15.0f), true));
		mushroom[i]->init();

		float scale = (rand() % 100) / 100.0f + 0.5f;
		float scaleY = (rand() % 100) / 200.0f + 0.5f;
		mushroom[i]->transform.scale(vec3(1.0f, scaleY, 1.0f));
	}

	const int rareMushroom = 5;
	GameObject *rareMusroom[rareMushroom];
	for (int i = 0; i < rareMushroom; i++) {
		int px = rand() % 1000 - 500;
		int py = 0;
		int pz = rand() % 1000 - 500;
		Model *modelTree = new Model("Tree1", "models/boletus/boletus_dae(collada)/boletus.dae");
		Material *multiMaterial3 = new Material("multiMaterial2", HSVShader);
		rareMusroom[i] = new GameObject("mushroom" + i);
		rareMusroom[i]->TerrainOffset = vec3(0, -1, 0);
		rareMusroom[i]->addComponent(modelTree);
		rareMusroom[i]->addComponent(multiMaterial3);
		rareMusroom[i]->addComponent(new RigidBody("shroomBody" + i, &_world, 10, vec3(px, py, pz), quat, true));
		rareMusroom[i]->addComponent(new AudioComponentLinear3D("shroomAudio"));
		rareMusroom[i]->init();

		rareMusroom[i]->transform.scale(0.2f);
	}

	
	const int numObstacles = 5; // Should be based on terrain boundary size. 
	GameObject *mountains[numObstacles];
	for (int i = 0; i < numObstacles; i++) {
		int px = rand() % 300 - 150;
		int py = rand() % 1;
		int pz = rand() % 300 - 150;
		Model *moutain = new Model("obstacle", "models/Rock1/Rock1.dae");
		Material *mountainMaterial = new Material("mountainMaterial", multiShadingProgram);
		mountains[i] = new GameObject("rocks" + i);
		mountains[i]->addComponent(moutain);
		mountains[i]->addComponent(mountainMaterial);
		mountains[i]->addComponent(new RigidBody("mountainBody" + i, &_world, 1, vec3(px, py, pz), true));
		mountains[i]->addComponent(new CollisionObject(vec3(15.0f, 5.0f, 15.0f), false, vec3(0.0f, 5.0f, 0.0f)));
		mountains[i]->init();
		mountains[i]->transform.scale(10.0f);
	}
	const int numGrass = 5;
	const int numClump = 5;
	const int totalGrass = numGrass * numClump;
	GameObject *grass[totalGrass];
	for (int i = 0; i < numGrass; i++) {
		int clumpPx = rand() % 1000 - 500;
		int clumpPy = rand() % 1000 - 500;
		for (int j = 0; j < numClump; j++) {
			int px = rand() % 200 - 100 + clumpPx;
			int py = -50;
			int pz = rand() % 200 - 100 + clumpPy;

			Model *grassModel = new Model("grassModel", "models/boletus/boletus_dae(collada)/boletus.dae");
			Material *grassMat = new Material("mountainMaterial", modelShader);
			grass[j] = new GameObject("grass" + to_string(i));
			grass[j]->TerrainOffset = vec3(0, -1, 0);
			grass[j]->addComponent(grassModel);
			grass[j]->addComponent(grassMat);
			grass[j]->addComponent(new RigidBody("mountainBody" + i, &_world, 10, vec3(px, py, pz), quat, true));
			grass[j]->init();
			grass[j]->transform.scale(((rand() % 2) + 1)/10.0f);
		}
	}

	GameObject skyBox("skyBox");
	skyBox.addComponent(skyBoxCube);
	skyBox.addComponent(skyboxMaterial);

	GameObject playerModel("playerModel");
	playerModel.addComponent(arissa);
	playerModel.addComponent(modelMat);
	playerModel.addComponent(new PlayerMovement("playerMovement", &inputHandler, &playerCamera));
	playerModel.addComponent(new RigidBody("playerBody", &_world, 100, vec3(0,50,0), true));
	playerModel.getComponent<Movement>()->attachGameObject(&playerModel);
	playerModel.addComponent(new CollisionObject(vec3(8.0f)));
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



	// Game Loop
	for (int i = 0; i < rareMushroom; i++) {
		rareMusroom[i]->getComponent<AudioComponent>()->playMusic("audio/music/sparkle.wav");
	}
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

		CollisionManager::getManager()->update();
		_world.stepSimulation(dt, 10);

		for (int i = 0; i < rareMushroom; i++) {
			rareMusroom[i]->getComponent<AudioComponentLinear3D>()->setSoundPosition(rareMusroom[i]->transform.calculateModelMatrix()[3]);
			rareMusroom[i]->getComponent<AudioComponentLinear3D>()->setListenerPosition(playerModel.transform.calculateModelMatrix()[3]);
		}
		
		//End of DeltaTime
		if (frameClock.alarm()) {

			// Process Inputs & Camera controls

			inputHandler.getMouse()->setLastPosition(inputHandler.getMouse()->getPosition());
			inputHandler.getMouse()->setLastScrollOffset(inputHandler.getMouse()->getScrollOffset());

			// End of Process Inputs

			// Update Function

			playerCamera.move();
			skyBox.transform.calculateModelMatrix();

			playerModel.transform.calculateModelMatrix();
			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function
			for (int i = 0; i < GameObject::gameObjects.size(); i++) {
				glRenderer.renderObject(GameObject::gameObjects[i]);
			}
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
