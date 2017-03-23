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
#include "Material.h"
#include "Shape.h"
#include "Model.h"

class GLRenderer : public Renderer
{
public:
	GLRenderer();
	virtual ~GLRenderer();

	void init();
	void renderObject(GameObject *obj);
	

};

