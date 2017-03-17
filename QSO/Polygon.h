#pragma once

#include "Mesh.h"

class Polygon
{
public:
	Polygon();
	virtual ~Polygon();

	Mesh *mesh[6];
	void init();

	void buildFace(Mesh *mesh, vec3 corner, vec3 up, vec3 right, vec3 normal, bool reverse);

};

