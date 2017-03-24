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


}

void PlayerMovement::update()
{
}
