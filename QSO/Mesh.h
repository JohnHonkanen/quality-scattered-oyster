#pragma once

#include <GL\glew.h>

#include "Component.h"


class MeshGenerator;

struct glData {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

};

struct MeshData {

	GLfloat *vertices;
	GLfloat *normals;
	GLfloat *color;
	GLfloat *uv;
	GLuint *indices;

	GLuint vertexCount;
	GLuint indexCount;
};

class Mesh :
	public Component
{
public:
	Mesh(std::string name);
	virtual ~Mesh();
	MeshData mesh;

	glData glObjects;

	void setData(GLuint vertexCount, GLuint indexCount, GLfloat *vertices, GLfloat *normals, GLfloat *color, GLfloat *uv, GLuint indices);
	void setData(GLuint vertexCount, GLuint indexCount, GLfloat *vertices, GLuint indices, GLfloat *normals, GLfloat *uv);
	void setData(GLuint vertexCount, GLuint indexCount, GLfloat *vertices, GLuint indices);
	//void init();

	void generateMesh();
};

