#pragma once
#include "GameObject.h"
class FlatTerrain :
	public GameObject
{
public:
	FlatTerrain(std::string name);
	virtual ~FlatTerrain();
};

