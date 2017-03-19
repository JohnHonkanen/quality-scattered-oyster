#include "Shape.h"



Shape::Shape()
{
}


Shape::~Shape()
{
}

vector<Mesh*> Shape::getMesh(int & numMeshs)
{
	numMeshs = Shape::numberOfMeshs;
	return Shape::meshes;
}
