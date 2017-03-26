#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include <map>
#include <iostream>
#include "Shape.h"
#include "simplex\SimplexNoise.h"

using namespace glm;

struct mapData {
	vec3 *vertices;
	vec3 *normals;
	vec2 *uv;
	GLuint *indices;

	int zLength;
	int xLength;
	int vertexCount;
	int indexCount;
	float **heightmap;
	float maxHeight = 0;
	float minHeight = 0;

	virtual void destroy() {
		//Deallocates Memory
		for (int i = 0; i < zLength; i++) {
			delete[] heightmap[i];
		}
		delete[] heightmap;
		delete[] vertices;
		delete[] normals;
		delete[] uv;
		delete[] indices;
	}
};

class Terrain :
	public Shape
{
private:
	void createMesh();
	void buildVertices();
	void calculateNormals();
	void buildIndices();

	float gridSize;

	mapData map;
public:
	Terrain(std::string name, int xLength, int zLength, float gridSize);
	virtual ~Terrain();
	void init();
	const mapData getData();
	void destroy();

	float getGridSize();
	vec3 position;
};

