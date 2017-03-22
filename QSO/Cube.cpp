#include "Cube.h"



void Cube::createMesh()
{
	init();
}

Cube::Cube(string name):Shape(name)
{
	createMesh();
}


Cube::~Cube()
{
}

void Cube::buildCube()
{

	GLfloat vertex[108] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f

	};

	GLfloat normal[108]{
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,

		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f
	};

	GLfloat uv[72]{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	GLuint indices[36];
	
	for (int i = 0; i < 36; i++) {
		indices[i] = i;
	}


	Mesh *mesh = new Mesh("cube");

	mesh->data.normals = normal;
	mesh->data.vertices = vertex;
	mesh->data.indices = indices;
	mesh->data.uv = uv;
	mesh->data.indexCount = 36;
	mesh->data.vertexCount = 36;
	mesh->setupMesh();

	Shape::meshes.push_back(mesh);

}

void Cube::buildCubeMap()
{
	GLfloat vertex[108]{
		// Positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	GLfloat normal[108]{
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,

		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f

	};

	GLfloat uv[72]{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	GLuint indices[36];

	for (int i = 0; i < 36; i++) {
		indices[i] = i;
	}

	Mesh *mesh = new Mesh("skybox");


	mesh->mesh.normals = normal;
	mesh->mesh.vertices = vertex;
	mesh->mesh.indices = indices;
	mesh->mesh.uv = uv;
	mesh->mesh.indexCount = 36;
	mesh->mesh.vertexCount = 36;
	mesh->generateMesh();

	Shape::meshes.push_back(mesh);
}

void Cube::init()
{
	Shape::numberOfMeshs = 1;
	buildCube();
	buildCubeMap();
}
