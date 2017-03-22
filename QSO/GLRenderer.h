#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include <iostream>

#include "Renderer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include "MeshGenerator.h"
#include "Mesh.h"
#include "Shape.h"
#include "Material.h"

class GLRenderer : public Renderer
{
public:
	GLRenderer();
	virtual ~GLRenderer();

	void init();
	void renderObject(Shape *shape, Transform transform, Material *material);
};

