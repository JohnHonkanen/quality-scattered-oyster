#pragma once
#include <assimp\scene.h>
#include <glm\glm.hpp>
#include <vector>
using namespace glm;
using namespace std;
class SkeletalBones
{
private:
	const char* name;
	int numWeights;
	vector<int> vertexIds;
	mat4 offsetMatrix;
	bool animated;
public:
	SkeletalBones();
	~SkeletalBones();

	

	void setOffsetMatrix(aiMatrix4x4 aiMat);
	void setVertexIds(vector<int> vertexIds);
	void setNumWeights(int numWeights);
	void setName(const char* name);
	void setAnimated(bool animated);
	
};

