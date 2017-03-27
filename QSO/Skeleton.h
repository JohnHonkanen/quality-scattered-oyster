#pragma once
#include <vector>
#include "SkeletalBones.h"
using namespace std;
class Skeleton
{
public:
	Skeleton();
	~Skeleton();

	vector<SkeletalBones> bones;
};

