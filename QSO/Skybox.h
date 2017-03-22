#pragma once
#include "Shape.h"

class Skybox :
	public Shape
{
private:
	void createMesh();
public:
	Skybox(string name);
	virtual ~Skybox();



};

