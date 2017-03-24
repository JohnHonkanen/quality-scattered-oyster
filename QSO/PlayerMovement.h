#pragma once
#include "Movement.h"
#include "Camera3rdPerson.h"

class PlayerMovement :
	public Movement
{

private:
	Camera3rdPerson *camera;
public:
	PlayerMovement(string name, glfwInputHandler *inputHandler, Camera3rdPerson *camera);
	virtual ~PlayerMovement();

	void pollInputs(double dt);
	void update();
};

