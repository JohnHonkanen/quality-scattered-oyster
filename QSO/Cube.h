#pragma once

#include "Mesh.h"
#include "Shape.h"

class Cube : public Shape
{
private:
	void createMesh();
public:
	Cube(TextureManager *textureManager, string textureName);
	virtual ~Cube();

	void init();
	void buildCube();
};

