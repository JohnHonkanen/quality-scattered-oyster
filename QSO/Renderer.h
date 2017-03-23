#pragma once

#include <GL\glew.h>
#include "Camera.h"
#include "GameObject.h"

class Renderer //Rendering Strategy
{
protected:
	Camera *camera;
public:
	Renderer();
	virtual ~Renderer();

	virtual void renderObject(GameObject *obj) = 0; // Handles the draw of the object
	void setCamera(Camera *camera);
};

