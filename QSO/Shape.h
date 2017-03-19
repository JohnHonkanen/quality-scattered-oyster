#pragma once

#include <vector>

#include "Mesh.h"

using namespace std;

class Shape
{
protected:
	int numberOfMeshs;
	vector<Mesh*> meshes;
public:
	Shape();
	virtual ~Shape();
	virtual void init() = 0;
	vector<Mesh*> getMesh(int &numMeshs);
	
};

