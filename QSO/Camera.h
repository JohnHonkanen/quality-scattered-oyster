#pragma once

#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glfw3.h>

#include "MouseInput.h"
#include "KeyboardInput.h"
class Camera
{
private:
	void updateCameraVectors();

protected:
	glm::mat4 view;
	glm::mat4 projection;
	float aspectRatio;
	float zNear;
	float zFar;

public:
	
	//Defines several possible options for camera movement. Ussed as abstraction to stay away from the window-system specific input methods.
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		NONE,
	};

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;

	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;
	GLfloat ZoomSensitivity;

	// Default Camera Values
	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVTY = 0.5f;
	const GLfloat ZOOM = 45.0f;
	const GLfloat ZOOMSENSITIVTY = 3.0f;

	// Default Constructor
	Camera();

	// Constructor with Vectors
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch); 
	
	//Constructor with Scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	virtual ~Camera();

	// Returns the view matrix calculated using Eular Angles and the glm::LookAt Matrix
	glm::mat4 GetViewMatrix();

	// Process Camera Key & Mouse Inputs
	void processCameraMouseMovement(MouseInput mouse, float dt, GLboolean clampPitch = true);
	void processMouseScroll(MouseInput mouse, float dt);
	void processKeyBoard(KeyboardInput keyboard, GLfloat deltaTime);

	// Set Camera Projection (Perspective/Orthographic) & View
	void setPerspectiveProjection(float FOV, float aspectRatio, float zNear, float zFar);
	void setOrthoProjection(glm::vec3 min, glm::vec3 max); // Set Ortho Camera in World Coordinates
	void setView(glm::vec3 position);
	glm::mat4 getProjection();
	glm::mat4 getView();

};

