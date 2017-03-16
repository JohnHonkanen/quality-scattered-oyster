#include "Camera.h"

// Currently, temp camera, needs upgrade.


/*
Calculates the front vector from the Camera's updated Eular Angles. 
Calculates the actual directon vector for the resulting yaw and pitch values using trig
Computes direction vector containing all the rotations calculated from the mouse's movement into cameraFront + normalize Front.
*/
void Camera::updateCameraVectors()
{
	// Calculates the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);

	// Re-calculate the Right and up vector

	// We normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement,
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));

}

Camera::Camera()
{
}

// Constructor with Vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = YAW;
	pitch = PITCH;
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	this->Position = glm::vec3(posX, posY, posZ);
	this->WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

Camera::~Camera()
{
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
	// For reference: glm::lookAt(eye, at, up)
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

// Process the input received from the mouse input system. Expects the offset value in both the x and y direction.
void Camera::processCameraMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean clampPitch)
{
	xOffset *= this->MouseSensitivity;
	yOffset *= this->MouseSensitivity;

	this->Yaw += xOffset;
	this->Pitch += yOffset;

	// We clamp the Pitch to make sure that when the pitch is out of bounds, screen doesn't get flipped. 
	// Euler Angle method doesn't allow for higher clamp range values. Need to use Quaternions for better spatial rotations.
	if (clampPitch) {
		if (this->Pitch > 89.0f) {
			this->Pitch = 89.0f;
		}
		
		if (this->Pitch < -89.0f) {
			this->Pitch = -89.0f;
		}
	}

	// Update Front, Right and Up vectors using the updated Eular angles.
	this->updateCameraVectors();
}

// Process input received from a mouse scroll-wheel event. Only requries input on the vertical wheel-axis.
void Camera::processMouseScroll(GLfloat yOffset)
{
	if (this->Zoom >= 1.0f && this->Zoom <= 45.0f) {
		//yOffset value represents the amount we scrolled vertically
		this->Zoom -= yOffset;
	}

	// Clamp the FOV to contain between 1.0f and 45.0f
	if (this->Zoom <= 1.0f) {
		this->Zoom = 1.0f;
	}

	if (this->Zoom >= 45.0f) {
		this->Zoom = 45.0f;
	}

}

// Process input received the keyboard. Accepts input parameters in the form of camera defined ENUM to abstract it from windowing systems.
void Camera::processKeyBoard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->MovementSpeed * deltaTime;
	if (direction == FORWARD) {
		this->Position += Front * velocity;
	}

	if (direction == BACKWARD) {
		this->Position -= this->Front * velocity;
	}

	if (direction == LEFT) {
		this->Position -= this->Right * velocity;
	}

	if (direction == RIGHT) {
		this->Position += this->Right * velocity;
	}

	// Make sure the user stays at the ground level by setting the y position to 0 and keep the camera at ground level (xz plane)
	this->Position.y = 0.0f;
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
