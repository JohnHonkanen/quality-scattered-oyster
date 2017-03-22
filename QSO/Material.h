#pragma once
#include <GL\glew.h>
#include <vector>

#include "Component.h"
#include "Shader.h"

using namespace std;

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

	bool isCubMap = false;

	vector<string> cubeMaps;
};

