#pragma once
#include "Movement.h"
#include "Camera3rdPerson.h"

#include "AudioComponent2D.h"

class PlayerMovement :
	public Movement
{

private:
	Camera3rdPerson *camera;
	float maxSpeed = 1.0f;
	AudioComponent2D *audioComponent;
public:
	PlayerMovement(string name, glfwInputHandler *inputHandler, Camera3rdPerson *camera);
	virtual ~PlayerMovement();
	void setMaxSpeed(float speed);
	void pollInputs(double dt);
	void update();
};

