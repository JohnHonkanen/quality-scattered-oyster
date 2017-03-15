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

using namespace std;

class SpriteRenderer : public Renderer
{
private:
	string fileLocation;
	string name;
	GLuint VAO, VBO, EBO; // 2D Mesh for the sprites
	TextureManager *textureManager;
	Transform *position; // Origin of the renderObject
	Shader *program;
public:
	SpriteRenderer(string fileLocation, string name, TextureManager *textureeManager, Transform *position, Shader *program);
	~SpriteRenderer();

	void init();
	void renderObject();
	void destroy();

};

