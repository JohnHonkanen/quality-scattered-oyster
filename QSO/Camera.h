#pragma once

#include <glm\glm.hpp>

#include "Component.h"

using namespace std;

class Camera : public Component
{
public:

	// Default Constructor
	Camera(string name);

	virtual ~Camera();

	virtual glm::mat4 getProjection() = 0;
	virtual glm::mat4 getView() = 0;
	virtual glm::vec3 getPosition() = 0;
	virtual void setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar) = 0;
	virtual void setOrthoProjection(glm::vec3 min, glm::vec3 max) = 0; // Set Ortho Camera in World Coordinates

};

