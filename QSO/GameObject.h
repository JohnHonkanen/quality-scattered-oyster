#pragma once
#include <vector>
#include "Object.h"
//Pre-Definition of Classes
class Transform;
class Component;

class GameObject :
	public Object
{
protected:
	std::vector<Component*> components;
public:
	GameObject(std::string name);
	virtual ~GameObject();
	template<class T>
	T *getComponent();
	void addComponent(Component* component);
	void destroy();
	Transform transform;

	static std::vector<GameObject*> gameObjects;
	static GameObject *find(std::string name);
};

