#pragma once
#include "Shapes.h"
#include "GLBasicMesh.h"
class Sprite :
	public Shapes
{
private:
	void createMesh();
public:
	Sprite(std::string spriteName, TextureManager *textureManager);
	Shapes* instantiate();
};

