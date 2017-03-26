#include "Terrain.h"


Terrain::Terrain(std::string name, const int xLength, const int zLength, float gridSize):Shape(name)
{
	Terrain::map.xLength = xLength;
	Terrain::map.zLength = zLength;
	Terrain::gridSize = gridSize;
	const int x = xLength;
	const int z = zLength;
	//Creating 2d array for heightmap and preallocate memory
	Terrain::map.heightmap = new float*[z]();
	for (int i = 0; i < z; i++) {
		Terrain::map.heightmap[i] = new float[x];
	}

	createMesh();
}


Terrain::~Terrain()
{
}

void Terrain::init()
{
	Terrain::buildVertices();
	Terrain::buildIndices();
	Terrain::calculateNormals();
}

const mapData Terrain::getData()
{
	return Terrain::map;
}

void Terrain::destroy()
{
	Terrain::map.destroy();
	delete this;
}

float Terrain::getGridSize()
{
	return gridSize;
}

void Terrain::createMesh()
{
	init();

	Mesh *mesh = new Mesh("terrainMesh");
	mesh->data.normals = (GLfloat *) map.normals;
	mesh->data.vertices = (GLfloat *) map.vertices;
	mesh->data.uv = (GLfloat *) map.uv;
	mesh->data.indices = map.indices;
	mesh->data.indexCount = map.indexCount;
	mesh->data.vertexCount = map.vertexCount;
	mesh->data.mode = GL_TRIANGLE_STRIP;
	mesh->setupMesh();
	Shape::numberOfMeshs = 1;
	Shape::meshes.push_back(mesh);
}

void Terrain::buildVertices()
{
	Terrain::map.vertexCount = Terrain::map.zLength*Terrain::map.zLength;
	//Preallocate vertices for normal
	Terrain::map.vertices = new vec3[Terrain::map.vertexCount]();
	Terrain::map.uv = new vec2[Terrain::map.vertexCount]();
	
	float textureU = Terrain::map.zLength * 1.0f;
	float textureV = Terrain::map.xLength * 1.0f;
	float frequency = 0.005f;
	float weight = 5.0f;

	int vertex = 0;
	for (int z = 0; z < Terrain::map.zLength; z++) {
		for (int x = 0; x < Terrain::map.zLength; x++) {
			float scaleU = float(z) / float(Terrain::map.zLength - 1);
			float scaleV = float(x) / float(Terrain::map.xLength - 1);
			float height = (SimplexNoise::noise(x * frequency * gridSize, z * frequency * gridSize) * weight)+2.0f;
			map.heightmap[z][x] = height;
			map.vertices[vertex] = vec3(x * Terrain::gridSize, height, -z* Terrain::gridSize); // Y is reserved for heightmap 
			map.uv[vertex] = vec2(textureU * scaleU, textureV * scaleV);
			vertex++;
			
		}
	}
}

void Terrain::calculateNormals()
{
	const int vCount = Terrain::map.vertexCount;
	std::vector<vec3> triangleNormals;
	//Preallocate memory for vectorMapping Array
	std::vector<vec3> *vectorMapping = new std::vector<vec3>[vCount];

	//Preallocate memory for normals
	Terrain::map.normals = new vec3[vCount];
	//Calculate Triangle Normals
	for (int i = 1; i < Terrain::map.indexCount;)
	{		
		int vertex1, vertex2, vertex3;
		vec3 point1, point2, point3;

		if (i == Terrain::map.indexCount - 1) {
			vertex1 = Terrain::map.indices[i - 1];
			vertex2 = Terrain::map.indices[i++];

			vec3 point1 = Terrain::map.vertices[vertex1];
			vec3 point2 = Terrain::map.vertices[vertex2];
			vec3 point3 = vec3(Terrain::map.xLength * Terrain::gridSize, 0, Terrain::map.zLength * Terrain::gridSize);

			vec3 edge1 = point2 - point1;
			vec3 edge2 = point3 - point1;
			vec3 normal = normalize(cross(edge1, edge2));
			if (normal.x == normal.x) {
				//Add our Triangle Normal
				triangleNormals.push_back(normal);

				//Map our normals to a vector
				vectorMapping[vertex1].push_back(normal);
				vectorMapping[vertex2].push_back(normal);
			}
		}
		else {
			vertex1 = Terrain::map.indices[i - 1];
			vertex2 = Terrain::map.indices[i++];
			vertex3 = Terrain::map.indices[i++];

			vec3 point1 = Terrain::map.vertices[vertex1];
			vec3 point2 = Terrain::map.vertices[vertex2];
			vec3 point3 = Terrain::map.vertices[vertex3];

			vec3 edge1 = point2 - point1;
			vec3 edge2 = point3 - point1;

			vec3 normal = normalize(cross(edge1, edge2));
			if (normal.x == normal.x) {
				//Add our Triangle Normal
				triangleNormals.push_back(normal);

				//Map our normals to a vector
				vectorMapping[vertex1].push_back(normal);
				vectorMapping[vertex2].push_back(normal);
				vectorMapping[vertex3].push_back(normal);
			}
		}
	} 
	//Calculate Vertex Normals
	for (int i = 0; i < vCount; i++) {
		//Get our triangle normal
		std::vector<vec3> triangleNormals = vectorMapping[i];
		vec3 normalSum = vec3(0);
		//Add our normals
		for (int n = 0; n < triangleNormals.size(); n++) {
			normalSum += triangleNormals[n];
			//if(i == 24)
			//cout << triangleNormals[n].x << "||" << triangleNormals[n].y << "||" << triangleNormals[n].z << endl;
		}
		
		vec3 vertexNormal = normalize(normalSum);
		//cout << i <<": "<< vertexNormal.x << "||" << vertexNormal.y << "||" << vertexNormal.z << endl;
		Terrain::map.normals[i] = vertexNormal;
	}

	delete[] vectorMapping;
}

void Terrain::buildIndices()
{
	//Find out how many indices we have
	const int numberOfStrips = Terrain::map.zLength - 1;
	const int numberOfDegens = 2 * (numberOfStrips - 1);
	const int verticesPerStrip = 2 * Terrain::map.xLength;

	//Calculates number of indices
	Terrain::map.indexCount = (verticesPerStrip*numberOfStrips) + numberOfDegens;
	Terrain::map.indices = new GLuint[Terrain::map.indexCount]();
	int offset = 0;
	for (int z = 0; z < Terrain::map.zLength-1; z++) {
		if (z > 0) {
			//Degenerate begin: Repeat the last Vertex, and increment
			Terrain::map.indices[offset++] = (z) * Terrain::map.zLength + (Terrain::map.xLength -1);
		}
		for (int x = Terrain::map.xLength - 1; x > -1; x--) {
			//Add a part of our strip
			Terrain::map.indices[offset++] = (z*Terrain::map.zLength) + x;
			Terrain::map.indices[offset++] = ((z + 1)*Terrain::map.zLength) + x;
			
		}

		if (z < Terrain::map.zLength - 2) {
			// Degenerate end: repeat first vertex
			Terrain::map.indices[offset++] = ((z + 1) * Terrain::map.zLength); // 
		}
	}
}
