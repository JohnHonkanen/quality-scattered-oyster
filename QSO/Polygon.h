#pragma once

#include "Mesh.h"

class Polygon
{
public:
	Polygon();
	virtual ~Polygon();

	Mesh *mesh[6];
	void init();

};

