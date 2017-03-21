#include "Polygon.h"



void Polygon::createMesh()
{
	init();
}

Polygon::Polygon(TextureManager *textureManager, string textureName) : Shape(textureManager)
{
	Shape::textureName = textureName;
	createMesh();
}


Polygon::~Polygon()
{
}

void Polygon::init()
{
	GLfloat polygonLength = 1.0f;

	Mesh* mesh0 = new Mesh("leftFace");
	buildFace(mesh0, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), false);
		
	Mesh* mesh1 = new Mesh("rightFace");
	buildFace(mesh1, vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), true);

	Mesh* mesh2 = new Mesh("bottomFace");
	buildFace(mesh2, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), false);

	Mesh* mesh3 = new Mesh("topFace");
	buildFace(mesh3, vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), true);

	Mesh* mesh4 = new Mesh("bottomFace");
	buildFace(mesh4, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), true);

	Mesh* mesh5 = new Mesh("frontFace");
	buildFace(mesh5, vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), false);

	Shape::numberOfMeshs = 6;
	Shape::meshes.push_back(mesh0);
	Shape::meshes.push_back(mesh1);
	Shape::meshes.push_back(mesh2);
	Shape::meshes.push_back(mesh3);
	Shape::meshes.push_back(mesh4);
	Shape::meshes.push_back(mesh5);
}

void Polygon::buildFace(Mesh * mesh, vec3 corner, vec3 up, vec3 right, bool reverse)
{
	GLfloat vertex[12];
	vertex[0] = corner.x;
	vertex[1] = corner.y;
	vertex[2] = corner.z;

	vec3 cVertex = corner + up;
	vertex[3] = cVertex.x;
	vertex[4] = cVertex.y;
	vertex[5] = cVertex.z;

	cVertex = corner + up + right;
	vertex[6] = cVertex.x;
	vertex[7] = cVertex.y;
	vertex[8] = cVertex.z;

	cVertex = corner + right;
	vertex[9] = cVertex.x;
	vertex[10] = cVertex.y;
	vertex[11] = cVertex.z;

	vec3 vertex1(vertex[0], vertex[1], vertex[2]);
	vec3 vertex2(vertex[3], vertex[4], vertex[5]);
	vec3 vertex3(vertex[6], vertex[7], vertex[8]);
	vec3 vertex4(vertex[9], vertex[10], vertex[11]);

	vec3 v1Normal = cross((vertex2 - vertex1), (vertex3 - vertex1));
	
	if (!reverse) {
		v1Normal = -v1Normal;
	}
	
	// Need to check if top/bottom and get correct normals
	if (mesh->toString() == "topFace" || mesh->toString() == "bottomFace") {
	//	v1Normal = -v1Normal;
	}

	GLfloat normal[12]{
		v1Normal.x, v1Normal.y, v1Normal.z,
		v1Normal.x, v1Normal.y, v1Normal.z,

		v1Normal.x, v1Normal.y, v1Normal.z,
		v1Normal.x, v1Normal.y, v1Normal.z

	};

	GLfloat uv[8] = {
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
	};

	if (reverse) {
		GLuint index[6] = {
			0, 1, 2,
			2, 3, 0
		};

		mesh->data.indices = index;
	}
	else {
		GLuint index[6] = {
			1, 0 ,2,
			3, 2, 0
		};

		mesh->data.indices = index;
	}

	mesh->data.normals = normal;
	mesh->data.vertices = vertex;
	mesh->data.uv = uv;
	mesh->data.indexCount = 6;
	mesh->data.vertexCount = 6;
	mesh->setupMesh();
	//printf("VAO2 %i \n", mesh->glObjects.VAO);
	
}
