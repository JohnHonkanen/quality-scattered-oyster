#pragma once
#include <vector>
#include "Material.h"
#include "Shape.h"


using namespace std;

class Model : public Shape
{
private:
	string modelLocation;
	void createMesh();
public:
	Model(string name, string modelLocation);
	virtual ~Model();
	vector<Material> material;
};

