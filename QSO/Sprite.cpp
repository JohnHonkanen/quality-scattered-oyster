#include "Sprite.h"



Sprite::Sprite(std::string spriteName, TextureManager *textureManager) : Shapes(textureManager, spriteName)
{
	Shapes::textureName = spriteName;
	Shapes::numberOfMeshs = 1;
	createMesh();
}

Shapes * Sprite::instantiate()
{
	Shapes *shape = new Sprite(Shapes::textureName, Shapes::textureManager);
	return shape;
}

void Sprite::createMesh()
{
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	GLfloat uv[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	Shapes::mesh = new GLBasicMesh(vertices, 4, uv, indices, 6, textureManager->getTexture(Shapes::textureName));
}
