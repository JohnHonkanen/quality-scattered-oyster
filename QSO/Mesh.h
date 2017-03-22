#pragma once

#include <GL\glew.h>

#include "Component.h"


class MeshGenerator;

struct MeshData {
	GLfloat *vertices;
	GLfloat *normals;
	GLfloat *color;
	GLfloat *uv;
	GLuint *indices;

	GLuint vertexCount;
	GLuint indexCount;
	GLenum mode;
};

class Mesh :
	public Component
{
private:
	GLuint VAO;
public:
	Mesh();
	Mesh(std::string name);
	virtual ~Mesh();
	void destroy();
	void setupMesh();
	void drawMesh();

	MeshData data;
	const GLuint getVAO();
};

