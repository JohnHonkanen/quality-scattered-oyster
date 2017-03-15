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
	MeshGenerator();
	virtual ~MeshGenerator();
};

