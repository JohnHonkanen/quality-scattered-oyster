#pragma once

#include <glm\glm.hpp>
#include <string>

#include "GameObject.h"
#include "Camera.h"
#include "glfwInputHandler.h"

using namespace std;
using namespace glm;
class Camera3rdPerson : public Camera
{
private:
	const float zoomSpeed = 3.0f;
	const float pitchSpeed = 0.3f;
	const float angleRotationSpeed = 0.3f;
	const vec2 distanceClamp = vec2(10.0f, 50.0f);
	const vec2 pitchClamp = vec2(5.0f, 85.0f);
	const vec3 atAdjustment = vec3(0.0f, 15.0f, 0.0f);
	float distanceToObject = 50;
	float angleAroundPlayer = 0;
	float pitch = 20;
	float yaw = 0;
	vec3 position;
	GameObject *gameObject;
	glfwInputHandler *inputHandler;

	mat4 projection;
	void calculateZoom();
	void calculatePitch();
	void calculateAngleAroundPlayer();

	float calculateHorizontalDistance();
	float calculateVerticalDistance();

	void calculateCameraPosition(float horizontalDistance, float verticalDistance);

public:
	Camera3rdPerson(string name, glfwInputHandler *inputHandler);
	virtual ~Camera3rdPerson();

	float getDistanceToObject();
	float getAngleAroundPlayer();
	float getPitch();
	float getYaw();
	void setAngleToObject();

	vec3 getPosition();

	void setObject(GameObject *gameObject);
	
	void move();
	void setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar);
	void setOrthoProjection(glm::vec3 min, glm::vec3 max); // Set Ortho Camera in World Coordinates
	mat4 getView();
	mat4 getProjection();
	vec3 getFront();
};

