#include "PlayerMovement.h"
#include "Rigidbody.h"


PlayerMovement::PlayerMovement(string name, glfwInputHandler *inputHandler, Camera3rdPerson *camera) : Movement(name, inputHandler)
{
	PlayerMovement::camera = camera;
}


PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::setMaxSpeed(float speed)
{
	maxSpeed = speed;
}

void PlayerMovement::pollInputs(double dt)
{
	KeyboardInput* keyboard = inputHandler->getKeyboard();
	RigidBody *rigidbody = gameObject->getComponent<RigidBody>();
	if (rigidbody == nullptr) {
		if (keyboard->keyPressed(GLFW_KEY_W)) {
			vec3 front = -normalize(camera->getPosition() - gameObject->transform.getPosition()) * 10.0f;
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
	else {
		btVector3 velocity = rigidbody->rigidbody->getLinearVelocity();
		btScalar speed = velocity.length();
		rigidbody->rigidbody->activate();
		if (keyboard->keyPressed(GLFW_KEY_W)) {
			vec3 front = -normalize(camera->getPosition() - gameObject->transform.getPosition()) * 10.0f;
			front.y = gameObject->transform.getPosition().y;
			vec3 moveForward = front;
			moveForward.y = velocity.y();
			rigidbody->rigidbody->setLinearVelocity(rigidbody->convertTobtVector3(moveForward));
		}


		if (keyboard->keyPressed(GLFW_KEY_S)) {
			vec3 front = -normalize(camera->getPosition() - gameObject->transform.getPosition()) * 10.0f;
			front.y = gameObject->transform.getPosition().y;
			vec3 moveBackwards= -front;
			rigidbody->rigidbody->setLinearVelocity(rigidbody->convertTobtVector3(moveBackwards));
		}

		if (!keyboard->keyPressed(GLFW_KEY_S) && !keyboard->keyPressed(GLFW_KEY_W)) {
			btVector3 linearVelocity = btVector3(0, velocity.y(), 0);
			rigidbody->rigidbody->setLinearVelocity(linearVelocity);
		}


		if (keyboard->keyPressed(GLFW_KEY_A)) {
			gameObject->transform.rotate(10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);
			btMatrix3x3 orientation = rigidbody->rigidbody->getWorldTransform().getBasis();
			orientation *= btMatrix3x3(btQuaternion(btVector3(0,1,0), radians(10.0f) *dt));
			rigidbody->rigidbody->getWorldTransform().setBasis(orientation);

		}


		if (keyboard->keyPressed(GLFW_KEY_D)) {
			gameObject->transform.rotate(-10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);
			btMatrix3x3 orientation = rigidbody->rigidbody->getWorldTransform().getBasis();
			orientation *= btMatrix3x3(btQuaternion(btVector3(0, 1, 0), radians(-10.0f) *dt));
			rigidbody->rigidbody->getWorldTransform().setBasis(orientation);
		}

		if (keyboard->keyPressed(GLFW_KEY_SPACE)) {
			rigidbody->rigidbody->applyCentralForce(btVector3(0,10,0));
		}
	}

	

}

void PlayerMovement::update()
{
}