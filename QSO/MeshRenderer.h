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

class MeshRenderer : public Renderer
{
private:
	Transform *transform; //Origin of the renderObject
	Shader *program;
public:
	MeshRenderer(Transform *transform, Shader *program);
	virtual ~MeshRenderer();

	void init();
	void renderObject(Mesh *mesh);
	void renderObject(Shape *shape);
};

