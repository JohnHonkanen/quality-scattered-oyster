#pragma once
#include "Object.h"
class GameObject;
class Component :
	public Object
{
public:
	Component(std::string name);
	virtual ~Component();
	GameObject *gameObject;
	Transform transform;
};
