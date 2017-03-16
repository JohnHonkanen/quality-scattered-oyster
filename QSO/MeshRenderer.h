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

struct Material {
	string texture;
	string diffuse;
	string specular;
	string emission;
	float shininess;
};

class MeshRenderer : public Renderer
{
private:
	Material material;
	TextureManager *textureManager;
	Transform *transform; //Origin of the renderObject
	Shader *program;
	Camera *camera;
	Mesh *mesh;

public:
	MeshRenderer(Mesh *mesh, Material material, TextureManager *textureManager, Transform *transform, Shader *program, Camera *camera);
	virtual ~MeshRenderer();

	void init();
	void renderObject();
};

