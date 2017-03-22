#pragma once

#include <vector>
#include "Component.h"
#include "TextureManager.h"
#include "Mesh.h"

using namespace std;

class Shape : public Component
{
protected:
	virtual void createMesh() = 0;
	int numberOfMeshs;
	vector<Mesh*> meshes;
public:
	Shape(string name);
	virtual ~Shape();
	void destroy();
	vector<Mesh*> getMesh(int &numMeshs);	
};

