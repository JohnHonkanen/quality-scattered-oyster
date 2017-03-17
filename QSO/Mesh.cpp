#include "Mesh.h"
#include "MeshGenerator.h"


Mesh::Mesh(std::string name): Component(name)
{
	Mesh::mesh.vertices = nullptr;
	Mesh::mesh.indices = nullptr;
	Mesh::mesh.color = nullptr;
	Mesh::mesh.uv = nullptr;
	Mesh::mesh.normals = nullptr;
}


Mesh::~Mesh()
{
}

void Mesh::setData(GLuint vertexCount, GLuint indexCount, GLfloat * vertices, GLuint indices)
{

}

void Mesh::generateMesh()
{
	glObjects.VAO = MeshGenerator::createMesh(mesh);
}
