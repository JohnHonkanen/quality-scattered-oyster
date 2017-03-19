#pragma once

#include "Mesh.h"
#include "Shape.h"

class Cube : public Shape
{
public:
	Cube();
	virtual ~Cube();

	void init();
	void buildCube();
};

