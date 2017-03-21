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

struct Material {
	string uv;
	string diffuse;
	string specular;
	string emission;
	string color;
	float shininess;
	
};

class GLRenderer : public Renderer
{
private:
	Shader *program;
public:
	GLRenderer(Shader *program);
	virtual ~GLRenderer();

	void init();
	void renderObject(Mesh *mesh, Transform transform);
	void renderObject(Shape *shape, Transform transform);
};

