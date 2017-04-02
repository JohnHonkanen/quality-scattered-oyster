#pragma once
#include "Component.h"
#include <string>

#include "glfwInputHandler.h"
#include "GameObject.h"


class Movement : public Component
{
protected:
	GameObject *gameObject;
	glfwInputHandler *inputHandler;
public:
	Movement(string name, glfwInputHandler *inputHandler);
	virtual void pollInputs(double dt) = 0;
	virtual void update() = 0;

	void attachGameObject(GameObject *gameObject);
};

