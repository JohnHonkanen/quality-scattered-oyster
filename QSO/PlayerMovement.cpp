#include "Terrain.h"
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

			GameObject *terrain = GameObject::find("terrain");
			Terrain *terrainShape = terrain->getComponent<Terrain>();
			mapData data = terrainShape->getData();
			GameObject *player = GameObject::find("playerModel");
			vec3 pos = player->transform.getPosition();
			float playerPosiX = pos.x;
			float playerPosiZ = pos.z;
			
			GameObject *obstacle0 = GameObject::find("rocks0");
			GameObject *obstacle1 = GameObject::find("rocks1");
			GameObject *obstacle2 = GameObject::find("rocks2");
			GameObject *obstacle3 = GameObject::find("rocks3");
			GameObject *obstacle4 = GameObject::find("rocks4");
			GameObject *obstacle5 = GameObject::find("rocks5");
			GameObject *obstacle6 = GameObject::find("rocks6");
			GameObject *obstacle7 = GameObject::find("rocks7");
			GameObject *obstacle8 = GameObject::find("rocks8");
			GameObject *obstacle9 = GameObject::find("rocks9");

			vec3 obsPos0 = obstacle0->transform.getPosition();
			vec3 obsPos1 = obstacle1->transform.getPosition();
			vec3 obsPos2 = obstacle2->transform.getPosition();
			vec3 obsPos3 = obstacle3->transform.getPosition();
			vec3 obsPos4 = obstacle4->transform.getPosition();
			vec3 obsPos5 = obstacle5->transform.getPosition();
			vec3 obsPos6 = obstacle6->transform.getPosition();
			vec3 obsPos7 = obstacle7->transform.getPosition();
			vec3 obsPos8 = obstacle8->transform.getPosition();
			vec3 obsPos9 = obstacle9->transform.getPosition();

			float obsPosiX0 = obsPos0.x;
			float obsPosiZ0 = obsPos0.z;

			float obsPosiX1 = obsPos1.x;
			float obsPosiZ1 = obsPos1.z;

			float obsPosiX2 = obsPos2.x;
			float obsPosiZ2 = obsPos2.z;

			float obsPosiX3 = obsPos3.x;
			float obsPosiZ3 = obsPos3.z;

			float obsPosiX4 = obsPos4.x;
			float obsPosiZ4 = obsPos4.z;

			float obsPosiX5 = obsPos5.x;
			float obsPosiZ5 = obsPos5.z;

			float obsPosiX6 = obsPos6.x;
			float obsPosiZ6 = obsPos6.z;

			float obsPosiX7 = obsPos7.x;
			float obsPosiZ7 = obsPos7.z;

			float obsPosiX8 = obsPos8.x;
			float obsPosiZ8 = obsPos8.z;

			float obsPosiX9 = obsPos9.x;
			float obsPosiZ9 = obsPos9.z;
			
			// Distance to player
			float distanceToPLayerX0 = obsPosiX0 - playerPosiX;
			float distanceToPlayerZ0 = obsPosiZ0 - playerPosiZ;

			float distanceToPLayerX1 = obsPosiX1 - playerPosiX;
			float distanceToPlayerZ1 = obsPosiZ1 - playerPosiZ;

			float distanceToPLayerX2 = obsPosiX2 - playerPosiX;
			float distanceToPlayerZ2 = obsPosiZ2 - playerPosiZ;

			float distanceToPLayerX3 = obsPosiX3 - playerPosiX;
			float distanceToPlayerZ3 = obsPosiZ3 - playerPosiZ;

			float distanceToPLayerX4= obsPosiX4 - playerPosiX;
			float distanceToPlayerZ4 = obsPosiZ4 - playerPosiZ;

			float distanceToPLayerX5 = obsPosiX5 - playerPosiX;
			float distanceToPlayerZ5 = obsPosiZ5 - playerPosiZ;

			float distanceToPLayerX6 = obsPosiX6 - playerPosiX;
			float distanceToPlayerZ6 = obsPosiZ6 - playerPosiZ;

			float distanceToPLayerX7 = obsPosiX7 - playerPosiX;
			float distanceToPlayerZ7 = obsPosiZ7 - playerPosiZ;

			float distanceToPLayerX8 = obsPosiX8 - playerPosiX;
			float distanceToPlayerZ8 = obsPosiZ8 - playerPosiZ;

			float distanceToPLayerX9 = obsPosiX9 - playerPosiX;
			float distanceToPlayerZ9 = obsPosiZ9 - playerPosiZ;


			float collisionDistance = 20.0f;
			float terrainX = pos.x - terrain->transform.physics[3].x;
			float terrainZ = pos.z - terrain->transform.physics[3].z;
			int gridX = (int)floor(terrainX / terrainShape->getGridSize());
			int gridZ = (int)floor(terrainZ / terrainShape->getGridSize());

			btVector3 velocity = rigidbody->rigidbody->getLinearVelocity();
			btScalar speed = velocity.length();
			rigidbody->rigidbody->activate();
			btVector3 linearVelocity = btVector3(0, velocity.y(), 0);
			rigidbody->rigidbody->setLinearVelocity(linearVelocity);


			if (gridX >= terrainShape->getData().xLength - 7 || gridZ >= terrainShape->getData().zLength - 7 || gridX < 6 || gridZ < 6 
				|| distanceToPLayerX0 <= collisionDistance && distanceToPLayerX0 >= -collisionDistance && distanceToPlayerZ0 <= collisionDistance && distanceToPlayerZ0 >= -collisionDistance
				|| distanceToPLayerX1 <= collisionDistance && distanceToPLayerX1 >= -collisionDistance && distanceToPlayerZ1 <= collisionDistance && distanceToPlayerZ1 >= -collisionDistance
				|| distanceToPLayerX2 <= collisionDistance && distanceToPLayerX2 >= -collisionDistance && distanceToPlayerZ2 <= collisionDistance && distanceToPlayerZ2 >= -collisionDistance
				|| distanceToPLayerX3 <= collisionDistance && distanceToPLayerX3 >= -collisionDistance && distanceToPlayerZ3 <= collisionDistance && distanceToPlayerZ3 >= -collisionDistance
				|| distanceToPLayerX4 <= collisionDistance && distanceToPLayerX4 >= -collisionDistance && distanceToPlayerZ4 <= collisionDistance && distanceToPlayerZ4 >= -collisionDistance
				|| distanceToPLayerX5 <= collisionDistance && distanceToPLayerX5 >= -collisionDistance && distanceToPlayerZ5 <= collisionDistance && distanceToPlayerZ5 >= -collisionDistance
				|| distanceToPLayerX6 <= collisionDistance && distanceToPLayerX6 >= -collisionDistance && distanceToPlayerZ6 <= collisionDistance && distanceToPlayerZ6 >= -collisionDistance
				|| distanceToPLayerX7 <= collisionDistance && distanceToPLayerX7 >= -collisionDistance && distanceToPlayerZ7 <= collisionDistance && distanceToPlayerZ7 >= -collisionDistance
				|| distanceToPLayerX8 <= collisionDistance && distanceToPLayerX8 >= -collisionDistance && distanceToPlayerZ8 <= collisionDistance && distanceToPlayerZ8 >= -collisionDistance
				|| distanceToPLayerX9 <= collisionDistance && distanceToPLayerX9 >= -collisionDistance && distanceToPlayerZ9 <= collisionDistance && distanceToPlayerZ9 >= -collisionDistance) {
				//printf("outside Terrain: \n");

				printf("!!!X %f \n", distanceToPLayerX0);
				printf("!!!Z %f \n", distanceToPlayerZ0);

				if (keyboard->keyPressed(GLFW_KEY_W)) {
					vec3 front = -normalize(camera->getPosition() - gameObject->transform.getPosition()) * 10.0f;
					front.y = gameObject->transform.getPosition().y;
					vec3 moveForward = front;
					moveForward.y = velocity.y();

					if (moveForward.x > -collisionDistance) {
						moveForward.x = 0;
					}

					if (moveForward.x < collisionDistance) {
						moveForward.x = 0;
					}

					if (moveForward.z > -collisionDistance) {
						moveForward.z = 0;
					}

					if (moveForward.z < collisionDistance) {
						moveForward.z = 0;
					}

					if (gridX >= terrainShape->getData().xLength - 7) {
						if (moveForward.x > 0) {
							moveForward.x = 0;
						}
					}

					if (gridX < 6) {
						if (moveForward.x < 0) {
							moveForward.x = 0;
						}
					}

					if (gridZ >= terrainShape->getData().xLength - 7) {
						if (moveForward.z > 0) {
							moveForward.z = 0;
						}
					}

					if (gridZ < 6 ) {
						if (moveForward.z < 0) {
							moveForward.z = 0;
						}
					}
					rigidbody->rigidbody->setLinearVelocity(rigidbody->convertTobtVector3(moveForward));
				}

				if (keyboard->keyPressed(GLFW_KEY_S)) {
					vec3 front = -normalize(camera->getPosition() - gameObject->transform.getPosition()) * 10.0f;
					front.y = gameObject->transform.getPosition().y;
					vec3 moveBackwards = -front;


					if (gridX >= terrainShape->getData().xLength - 7) {
						if (moveBackwards.x > 0) {
							moveBackwards.x = 0;
						}
					}

					if (gridX < 6) {
						if (moveBackwards.x < 0) {
							moveBackwards.x = 0;
						}
					}

					if (gridZ >= terrainShape->getData().xLength - 7) {
						if (moveBackwards.z > 0) {
							moveBackwards.z = 0;
						}
					}

					if (gridZ < 6) {
						if (moveBackwards.z < 0) {
							moveBackwards.z = 0;
						}
					}

					rigidbody->rigidbody->setLinearVelocity(rigidbody->convertTobtVector3(moveBackwards));
				}

				if (!keyboard->keyPressed(GLFW_KEY_S) && !keyboard->keyPressed(GLFW_KEY_W)) {
					btVector3 linearVelocity = btVector3(0, velocity.y(), 0);
					rigidbody->rigidbody->setLinearVelocity(linearVelocity);
				}


				if (keyboard->keyPressed(GLFW_KEY_A)) {
					gameObject->transform.rotate(10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);
					btMatrix3x3 orientation = rigidbody->rigidbody->getWorldTransform().getBasis();
					orientation *= btMatrix3x3(btQuaternion(btVector3(0, 1, 0), radians(10.0f) *dt));
					rigidbody->rigidbody->getWorldTransform().setBasis(orientation);

				}


				if (keyboard->keyPressed(GLFW_KEY_D)) {
					gameObject->transform.rotate(-10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);
					btMatrix3x3 orientation = rigidbody->rigidbody->getWorldTransform().getBasis();
					orientation *= btMatrix3x3(btQuaternion(btVector3(0, 1, 0), radians(-10.0f) *dt));
					rigidbody->rigidbody->getWorldTransform().setBasis(orientation);
				}
			}
			else {

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
				vec3 moveBackwards = -front;
				rigidbody->rigidbody->setLinearVelocity(rigidbody->convertTobtVector3(moveBackwards));
			}

			if (!keyboard->keyPressed(GLFW_KEY_S) && !keyboard->keyPressed(GLFW_KEY_W)) {
				btVector3 linearVelocity = btVector3(0, velocity.y(), 0);
				rigidbody->rigidbody->setLinearVelocity(linearVelocity);
			}


			if (keyboard->keyPressed(GLFW_KEY_A)) {
				gameObject->transform.rotate(10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);
				btMatrix3x3 orientation = rigidbody->rigidbody->getWorldTransform().getBasis();
				orientation *= btMatrix3x3(btQuaternion(btVector3(0, 1, 0), radians(10.0f) *dt));
				rigidbody->rigidbody->getWorldTransform().setBasis(orientation);

			}


			if (keyboard->keyPressed(GLFW_KEY_D)) {
				gameObject->transform.rotate(-10.0f * dt, vec3(0.0f, 1.0f, 0.0f), false);
				btMatrix3x3 orientation = rigidbody->rigidbody->getWorldTransform().getBasis();
				orientation *= btMatrix3x3(btQuaternion(btVector3(0, 1, 0), radians(-10.0f) *dt));
				rigidbody->rigidbody->getWorldTransform().setBasis(orientation);
			}

			if (keyboard->keyPressed(GLFW_KEY_SPACE)) {
				rigidbody->rigidbody->applyCentralForce(btVector3(0, 10, 0));
			}
		}
	}
}

void PlayerMovement::update()
{
}