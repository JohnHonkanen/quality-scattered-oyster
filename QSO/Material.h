#pragma once
#include <GL\glew.h>
#include <vector>

#include "Component.h"
#include "Shader.h"

using namespace std;

enum TEXTURE_TYPE {
	DIFFUSE = 0,
	SPECULAR = 1,
	EMISSION = 2,
	NO_TEXTURE_TYPE = -1
};

struct Texture{
	string textureName; 
	TEXTURE_TYPE type;
	int number;
};

class Material :
	public Component
{
public:
	Material();
	Material(string name, Shader program);
	virtual ~Material();
	Shader program;

	void addTexture(string textureName, TEXTURE_TYPE type, int number = 1);
	string convertTypeToString(TEXTURE_TYPE);
	bool isCubMap = false;

	vector<string> cubeMaps;
	vector<Texture> textures;
};
