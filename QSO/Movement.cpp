#include "Movement.h"

Movement::Movement(string name, glfwInputHandler * inputHandler) : Component(name)
{
	Movement::inputHandler = inputHandler;
}

void Movement::attachGameObject(GameObject * gameObject)
{
	Movement::gameObject = gameObject;
}
