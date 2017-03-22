#pragma once

#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"
#include "Shape.h"
#include "Material.h"

class Renderer //Rendering Strategy
{
protected:
	Camera *camera;
public:
	Renderer();
	virtual ~Renderer();

	virtual void renderObject(Shape *shape, Transform transform, Material *material) = 0; // Handles the draw of the object
	void setCamera(Camera *camera);
};

