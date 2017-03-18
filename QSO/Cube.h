#pragma once

#include "Mesh.h"

class Cube
{
public:
	Cube();
	virtual ~Cube();

	Mesh *mesh[6];
	void init(Mesh * mesh);
};

