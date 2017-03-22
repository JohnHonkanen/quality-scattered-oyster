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
		meshes[i]->destroy();
	}
}

vector<Mesh*> Shape::getMesh(int & numMeshs)
{
	numMeshs = Shape::numberOfMeshs;
	return Shape::meshes;
}