#include "Terrain.h"



Terrain::Terrain(std::string name, const int xBlocks, const int zBlocks, float gridSize):Component(name)
{
	Terrain::xBlocks = xBlocks;
	Terrain::zBlocks = zBlocks;
	Terrain::gridSize = gridSize;
	const int x = xBlocks;
	const int z = zBlocks;
	//Creating 2d array for heightmap and preallocate memory
	heightmap = new float*[z]();
	for (int i = 0; i < z; i++) {
		heightmap[i] = new float[x];
	}

}


Terrain::~Terrain()
{
	//Deallocates Memory
	for (int i = 0; i < Terrain::zBlocks; i++) {
		delete[] heightmap[i];
	}
	delete[] heightmap;
}

void Terrain::init()
{
	Terrain::buildVertices();
	Terrain::calculateNormals();
	Terrain::buildIndices();
}

void Terrain::buildVertices()
{

}

void Terrain::calculateNormals()
{
}

void Terrain::buildIndices()
{
}
