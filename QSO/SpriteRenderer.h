#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>
#include <iostream>

#include "Renderer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Shader.h"
#include "MeshGenerator.h"
#include "Camera.h"

using namespace std;

class SpriteRenderer : public Renderer
{
private:
	string fileLocation;
	string name;
	GLuint VAO; // 2D Mesh for the sprites
	TextureManager *textureManager;
	Transform *position; // Origin of the renderObject
	Shader *program;
	Camera *camera;
public:
	SpriteRenderer(string fileLocation, string name, TextureManager *textureeManager, Transform *position, Shader *program, Camera *camera);
	~SpriteRenderer();

	void init();
	void renderObject();
	void destroy();

};

