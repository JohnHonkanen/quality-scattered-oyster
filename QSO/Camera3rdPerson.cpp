#include "Camera3rdPerson.h"

Camera3rdPerson::Camera3rdPerson(string name, glfwInputHandler * inputHandler) : Camera(name)
{
	Camera3rdPerson::inputHandler = inputHandler;
}

Camera3rdPerson::~Camera3rdPerson()
{
}

float Camera3rdPerson::getDistanceToObject()
{
	return distanceToObject;
}

float Camera3rdPerson::getAngleAroundPlayer()
{
	return angleAroundPlayer;
}

float Camera3rdPerson::getPitch()
{
	return pitch;
}

float Camera3rdPerson::getYaw()
{
	return yaw;
}

void Camera3rdPerson::setAngleToObject()
{
	angleAroundPlayer = gameObject->transform.getRotation().y;
}

vec3 Camera3rdPerson::getPosition()
{
	return position;
}

void Camera3rdPerson::setObject(GameObject * gameObject)
{
	Camera3rdPerson::gameObject = gameObject;
}

void Camera3rdPerson::move()
{
	calculateZoom();
	calculatePitch();
	calculateAngleAroundPlayer();
	float horizontalDistance = calculateHorizontalDistance();
	float verticalDistance = calculateVerticalDistance();
	calculateCameraPosition(horizontalDistance, verticalDistance);
	Camera3rdPerson::yaw = 180 - (gameObject->transform.getRotation().y + angleAroundPlayer);
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));

}

void Camera3rdPerson::calculateZoom()
{
	float yOffset = inputHandler->getMouse()->getScrollOffset().y;
	distanceToObject -= yOffset * zoomSpeed;
	distanceToObject = clamp(distanceToObject, distanceClamp.x, distanceClamp.y);
	inputHandler->getMouse()->setScrollOffset(vec2(0));
}

void Camera3rdPerson::calculatePitch()
{
	MouseInput *mouse = inputHandler->getMouse();
	if (mouse->getButtonPressed(0)) {
		float pitchChange = mouse->getOffset().y;
		pitch -= pitchChange * pitchSpeed;
		pitch = clamp(pitch, pitchClamp.x, pitchClamp.y);
	}
}

void Camera3rdPerson::calculateAngleAroundPlayer()
{
	MouseInput *mouse = inputHandler->getMouse();
	
	if (mouse->getButtonPressed(1)) {
		float angleChange = mouse->getOffset().x;
		angleAroundPlayer += angleChange * angleRotationSpeed;
	}
	else {
		angleAroundPlayer = (1.0f - lerpAmount) * angleAroundPlayer + lerpAmount * gameObject->transform.getRotation().y;
	}
}

float Camera3rdPerson::calculateHorizontalDistance()
{
	return distanceToObject*cos(radians(pitch));
}

float Camera3rdPerson::calculateVerticalDistance()
{
	return distanceToObject*sin(radians(pitch));
}

void Camera3rdPerson::calculateCameraPosition(float horizontalDistance, float verticalDistance)
{
	vec3 objectRotation = gameObject->transform.getRotation();
	float theta = (objectRotation.y + radians(angleAroundPlayer));
	float offSetX = horizontalDistance * sin(theta);
	float offSetZ = horizontalDistance * cos(theta);

	position = gameObject->transform.getPosition() + vec3(-offSetX, verticalDistance, -offSetZ);
}

void Camera3rdPerson::setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar)
{
	Camera3rdPerson::projection = glm::perspective(FOV, aspectRatio, zNear, zFar);
}

void Camera3rdPerson::setOrthoProjection(glm::vec3 min, glm::vec3 max)
{
	Camera3rdPerson::projection = glm::ortho(min.x, max.x, min.y, max.y, min.z, max.z);
}

mat4 Camera3rdPerson::getView()
{ 
	mat4 view(1.0f);
	view = lookAt(position, gameObject->transform.getPosition() + atAdjustment, vec3(0.0f, 1.0f, 0.0f)); //translate(view, position)

	return view;
}

mat4 Camera3rdPerson::getProjection()
{
	return projection;
}

vec3 Camera3rdPerson::getFront()
{
	return normalize(vec3(getView() * vec4(0.0f, 0.0f, -1.0f, 0.0f))); //  normalize(front)
}
