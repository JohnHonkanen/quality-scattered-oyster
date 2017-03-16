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
	front.x = cos(glm::radians(Camera::Yaw)) * cos(glm::radians(Camera::Pitch));
	front.y = sin(glm::radians(Camera::Pitch));
	front.z = sin(glm::radians(Camera::Yaw)) * cos(glm::radians(Camera::Pitch));
	Camera::Front = glm::normalize(front);

	// Re-calculate the Right and up vector

	// We normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement,
	Camera::Right = glm::normalize(glm::cross(Camera::Front, Camera::WorldUp));
	Camera::Up = glm::normalize(glm::cross(Camera::Right, Camera::Front));

}

Camera::Camera()
{
}

// Constructor with Vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	position = glm::vec3(0.0f, 0.0f, 10.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = YAW;
	pitch = PITCH;
	Camera::MouseSensitivity = SENSITIVTY;
	Camera::MovementSpeed = SPEED;
	Camera::Zoom = ZOOM;
	Camera::ZoomSensitivity = ZOOMSENSITIVTY;
	Camera::Position = position;
	Camera::WorldUp = up;
	Camera::Yaw = yaw;
	Camera::Pitch = pitch;
	Camera::updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	Camera::Position = glm::vec3(posX, posY, posZ);
	Camera::WorldUp = glm::vec3(upX, upY, upZ);
	Camera::Yaw = yaw;
	Camera::Pitch = pitch;
	Camera::updateCameraVectors();
}

Camera::~Camera()
{
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
	// For reference: glm::lookAt(eye, at, up)
	mat4 view = glm::lookAt( Camera::Position, Camera::Position + Camera::Front, Camera::Up);
	vec3 at = Camera::Position + Camera::Front;
	/*printf("Eye: (%f,%f,%f)\n", Camera::Position.x, Camera::Position.y, Camera::Position.z);
	printf("At: (%f,%f,%f)\n", at.x, at.y, at.z);
	printf("Front: (%f,%f,%f)\n", Camera::Front.x, Camera::Front.y, Camera::Front.z);
	printf("view: (%f,%f,%f)\n", view[3].x, view[3].y, view[3].z);*/
	return view;
}

// Process the input received from the mouse input system. Expects the offset value in both the x and y direction.
void Camera::processCameraMouseMovement(MouseInput mouse, float dt,GLboolean clampPitch)
{
	if (mouse.getPosition() == mouse.getLastPosition())
		return;

	vec2 offset = mouse.getOffset();
	//printf("Mouse Position (%f,%f)\n", offset.x, offset.y);
	float xOffset = offset.x;
	float yOffset = offset.y;

	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Camera::Yaw += xOffset;
	Camera::Pitch += yOffset;

	// We clamp the Pitch to make sure that when the pitch is out of bounds, screen doesn't get flipped. 
	// Euler Angle method doesn't allow for higher clamp range values. Need to use Quaternions for better spatial rotations.
	if (clampPitch) {
		if (Camera::Pitch > 89.0f) {
			Camera::Pitch = 89.0f;
		}
		
		if (Camera::Pitch < -89.0f) {
			Camera::Pitch = -89.0f;
		}
	}

	// Update Front, Right and Up vectors using the updated Eular angles.
	Camera::updateCameraVectors();
}

// Process input received from a mouse scroll-wheel event. Only requries input on the vertical wheel-axis.
void Camera::processMouseScroll(MouseInput mouse, float dt)
{
	float yOffset = mouse.getScrollOffset().y;

	//yOffset value represents the amount we scrolled vertically
	Camera::Zoom -= yOffset * dt * Camera::ZoomSensitivity;
	printf("Mouse Zoom: %f \n", Camera::Zoom);

	// Clamp the FOV to contain between 1.0f and 45.0f
	Camera::Zoom = clamp(Camera::Zoom, 2.0f, 44.0f);
	

	Camera::setPerspectiveProjection(glm::radians(Camera::Zoom), Camera::aspectRatio, Camera::zNear, Camera::zFar);
}

// Process input received the keyboard. Accepts input parameters in the form of camera defined ENUM to abstract it from windowing systems.
void Camera::processKeyBoard(KeyboardInput keyboard, GLfloat deltaTime)
{
	Camera_Movement direction = NONE;
	if (keyboard.keyPressed(GLFW_KEY_W))
		direction = FORWARD;
	if (keyboard.keyPressed(GLFW_KEY_S))
		direction = BACKWARD;
	if (keyboard.keyPressed(GLFW_KEY_A))
		direction = LEFT;
	if (keyboard.keyPressed(GLFW_KEY_D))
		direction = RIGHT;

	GLfloat velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD) {
		Camera::Position += Front * velocity;
	}

	if (direction == BACKWARD) {
		Camera::Position -= Camera::Front * velocity;
	}

	if (direction == LEFT) {
		Camera::Position -= Camera::Right * velocity;
	}

	if (direction == RIGHT) {
		Camera::Position += Camera::Right * velocity;
	}

	// Make sure the user stays at the ground level by setting the y position to 0 and keep the camera at ground level (xz plane)
	Camera::Position.y = 0.0f;
}

void Camera::setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar)
{
	Camera::aspectRatio = aspectRatio;
	Camera::zNear = zNear;
	Camera::zFar = zFar;
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
	view = Camera::GetViewMatrix();
	return view;
}
