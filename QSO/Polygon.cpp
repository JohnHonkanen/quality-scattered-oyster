#include "Polygon.h"



Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}

void Polygon::init()
{
	GLfloat polygonLength = 1.0f;

	mesh[0] = new Mesh("leftFace");
	buildFace(mesh[0], vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), false);
		
	mesh[1] = new Mesh("rightFace");
	buildFace(mesh[1], vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), true);

	mesh[2] = new Mesh("bottomFace");
	buildFace(mesh[2], vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), false);

	mesh[3] = new Mesh("topFace");
	buildFace(mesh[3], vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), true);

	mesh[4] = new Mesh("bottomFace");
	buildFace(mesh[4], vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), true);

	mesh[5] = new Mesh("frontFace");
	buildFace(mesh[5], vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), false);
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

		mesh->mesh.indices = index;
	}
	else {
		GLuint index[6] = {
			1, 0 ,2,
			3, 2, 0
		};

		mesh->mesh.indices = index;
	}

	mesh->mesh.normals = normal;
	mesh->mesh.vertices = vertex;
	mesh->mesh.uv = uv;
	mesh->mesh.indexCount = 6;
	mesh->mesh.vertexCount = 6;
	mesh->generateMesh();
	
	
}

