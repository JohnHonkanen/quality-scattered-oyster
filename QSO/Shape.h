#pragma once

#include <vector>
#include "TextureManager.h"
#include "Mesh.h"

using namespace std;

class Shape
{
protected:
	virtual void createMesh() = 0;
	int numberOfMeshs;
	vector<Mesh*> meshes;
	string textureName;
	TextureManager *textureManager;
public:
	Shape(TextureManager *textureManager);
	virtual ~Shape();
	vector<Mesh*> getMesh(int &numMeshs);
	GLuint getTexture();
	
};

