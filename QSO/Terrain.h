#pragma once
#include <glm.hpp>
#include "Component.h"
#include "Mesh.h"

using namespace glm;

struct mapData {
	vec3 *vertices;
	vec3 *normals;
	vec3 *uv;
	vec3 *indices;
};

class Terrain :
	public Component
{
protected:
	Mesh *mesh;
	int zBlocks;
	int xBlocks;
	float **heightmap;
	mapData data;
public:
	Terrain(std::string name, int xSize, int zSize, float gridSize);
	virtual ~Terrain();

	void init();
	void buildVertices();
	void calculateNormals();
	void buildIndices();

	float gridSize;
	vec3 position;
};

