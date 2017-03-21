#include "Shape.h"



Shape::Shape(TextureManager *textureManager) :Component("")
{
	Shape::textureManager = textureManager;
}


Shape::~Shape()
{
}

vector<Mesh*> Shape::getMesh(int & numMeshs)
{
	numMeshs = Shape::numberOfMeshs;
	return Shape::meshes;
}

GLuint Shape::getTexture()
{
	return textureManager->getTexture(textureName);
}
