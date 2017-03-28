#include "Shape.h"



Shape::Shape(string name) :Component(name)
{
}


Shape::~Shape()
{
}

void Shape::destroy()
{
	for (int i = 0; i < numberOfMeshs; i++) {
		if (meshes[i] != nullptr) {
			meshes[i]->destroy();
			meshes[i] = nullptr;
		}
	}
}

vector<Mesh*> Shape::getMesh(int & numMeshs)
{
	numMeshs = Shape::numberOfMeshs;
	return Shape::meshes;
}