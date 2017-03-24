#pragma once
#include "Movement.h"

class PlayerMovement :
	public Movement
{
public:
	PlayerMovement(string name, glfwInputHandler *inputHandler);
	virtual ~PlayerMovement();

	void pollInputs();
	void update();
};

