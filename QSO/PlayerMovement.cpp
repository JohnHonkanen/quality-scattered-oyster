#include "PlayerMovement.h"



PlayerMovement::PlayerMovement(string name, glfwInputHandler *inputHandler, Camera3rdPerson *camera) : Movement(name, inputHandler)
{
	PlayerMovement::camera = camera;
}


PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::pollInputs(double dt)
{
	KeyboardInput* keyboard = inputHandler->getKeyboard();

	if (keyboard->keyPressed(GLFW_KEY_W)) {
		vec3 front = -normalize(camera->getPosition()-gameObject->transform.getPosition()) * 10.0f;
		front.y = gameObject->transform.getPosition().y;
		vec3 moveForward = front;
		
		gameObject->transform.translate(moveForward * (float)dt);
	}


	if (keyboard->keyPressed(GLFW_KEY_S)) {
		vec3 front = -normalize(camera->getPosition() - gameObject->transform.getPosition()) * 10.0f;
		front.y = gameObject->transform.getPosition().y;
		vec3 moveForward = -front;

		gameObject->transform.translate(moveForward * (float)dt);
	}


	if (keyboard->keyPressed(GLFW_KEY_A)) {
		
		gameObject->transform.rotate(10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);

	}


	if (keyboard->keyPressed(GLFW_KEY_D)) {
		gameObject->transform.rotate(-10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);
	}

}

void PlayerMovement::update()
{
}
