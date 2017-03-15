#include "Camera.h"

// Currently, temp camera, needs upgrade.

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar)
{
	Camera::projection = glm::perspective(FOV, aspectRatio, zNear, zFar);
}

void Camera::setOrthoProjection(glm::vec3 min, glm::vec3 max)
{
	Camera::projection = glm::ortho(min.x, max.x, min.y, max.y, min.z, max.z);
}

void Camera::setView(glm::vec3 position)
{
	view = translate(view, position);
}

glm::mat4 Camera::getProjection()
{
	return Camera::projection;
}

glm::mat4 Camera::getView()
{
	return Camera::view;
}
