#pragma once
#include "Object.h"
#include "Transform.h"
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
