#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
protected:
	glm::mat4 view;
	glm::mat4 projection;
public:
	Camera();
	virtual ~Camera();

	void setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar);
	void setOrthoProjection(glm::vec3 min, glm::vec3 max); // Set Ortho Camera in World Coordinates
	void setView(glm::vec3 position);
	
	glm::mat4 getProjection();
	glm::mat4 getView();
};

