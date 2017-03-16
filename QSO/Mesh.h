#pragma once
#include "Component.h"
#include <GL\glew.h>
struct MeshData {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};
class Mesh :
	public Component
{
public:
	Mesh(std::string name);
	virtual ~Mesh();
	MeshData mesh;

};

