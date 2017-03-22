#pragma once

#include "Mesh.h"
#include "Shape.h"

class Cube : public Shape
{
private:
	void createMesh();
public:
	Cube(string name);
	virtual ~Cube();

	void init();
	void buildCube();
	/*void buildCubeMap();*/
};

