#pragma once
#include <GL\glew.h>
#include "Component.h"
#include "Shader.h"
class Material :
	public Component
{
public:
	Material(string name, Shader program);
	virtual ~Material();
	Shader program;
	string diffuseMap;
	string specularMap;
	string emissionMap;
};

