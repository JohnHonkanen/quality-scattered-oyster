#include "Mesh.h"
#include "MeshGenerator.h"


Mesh::Mesh() : Component("")
{

}

Mesh::Mesh(std::string name): Component(name)
{
	Mesh::data.vertices = nullptr;
	Mesh::data.indices = nullptr;
	Mesh::data.color = nullptr;
	Mesh::data.uv = nullptr;
	Mesh::data.normals = nullptr;
	Mesh::data.mode = GL_TRIANGLES; // Default Mode
}


Mesh::~Mesh()
{
}

void Mesh::destroy()
{
	delete this;
}

void Mesh::setupMesh()
{
	VAO = MeshGenerator::createMesh(data);
}

void Mesh::drawMesh()
{
	

	if (data.indices != nullptr) {
		glDrawElements(data.mode, data.indexCount, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(data.mode, 0, 36);
	}
	
	glBindVertexArray(0);
}

const GLuint Mesh::getVAO()
{
	return VAO;
}
