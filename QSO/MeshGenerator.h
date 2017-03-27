#pragma once

#include <GL\glew.h>
#include <map>
#include <iostream>

#include "Mesh.h"

#define STORED_VERTEX       0
#define STORED_COLOR        1
#define STORED_UV           2
#define STORED_NORMAL		3
#define STORED_INDEX		4
#define STORED_TANGENT		5
#define STORED_BITANGENT	6

using namespace std;

class MeshGenerator
{
public:
	//static GLuint createMesh(const GLfloat *data, size_t sizeOfData, const GLuint *indices, size_t sizeOfIndices);
	static void updateMesh(const GLuint mesh, const unsigned int bufferType, const GLfloat *data, const GLuint size);
	static void destroy();
	static map<GLuint, GLuint*> VAOMap;

	static GLuint createMesh(MeshData data);
};

