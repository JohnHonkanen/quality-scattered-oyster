#include "Model.h"
#include "AssimpLoader.h"

void Model::createMesh()
{
	Shape::meshes = AssimpLoader::loadModel(modelLocation, material);
	Shape::numberOfMeshs = meshes.size();
}

Model::Model(string name, string modelLocation) : Shape(name)
{
	Model::modelLocation = modelLocation;
	createMesh();
}

Model::~Model()
{
}
