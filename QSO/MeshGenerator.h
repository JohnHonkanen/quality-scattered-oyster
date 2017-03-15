#pragma once

#include  <GL\glew.h>
#include <map>

#define STORED_VAO      0
#define STORED_VBO      1
#define STORED_EBO      2

using namespace std;

class MeshGenerator
{
public:
	static void createMesh(const GLfloat *data, const GLuint *indices, GLuint *VAO, GLuint *VBO, GLuint *EBO);
	static void updateMesh(const GLuint mesh, const unsigned int bufferType, const GLfloat *data, const GLuint size);
	static void destroy();
	static map<GLuint, GLuint*> VAOMap;
};

