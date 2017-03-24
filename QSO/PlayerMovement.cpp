#include "PlayerMovement.h"



PlayerMovement::PlayerMovement(string name, glfwInputHandler *inputHandler) : Movement(name, inputHandler)
{
}


PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::pollInputs()
{
	KeyboardInput* keyboard = inputHandler->getKeyboard();

	/*if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) {
			keyboard->setKey(key, true);
			cout << "key pressed " << key << endl;
		}
		else if (action == GLFW_RELEASE) {
			keyboard->setKey(key, false);
			cout << "key released" << endl;
		}*/
}

void PlayerMovement::update()
{
}
