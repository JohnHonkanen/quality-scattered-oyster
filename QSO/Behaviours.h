#pragma once
#include "Component.h"
class Behaviours :
	public Component
{
public:
	Behaviours(std::string name);
	bool enabled = true;
};

