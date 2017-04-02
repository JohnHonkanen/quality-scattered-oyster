#pragma once
#include <vector>
#include "Object.h"
#include "Transform.h"
//Pre-Definition of Classes
class Component;

class GameObject :
	public Object
{
protected:
	std::vector<Component*> components;
public:
	GameObject(std::string name);
	virtual ~GameObject();
	void init();
	template<class T>
	T *getComponent();
	void addComponent(Component* component);
	void destroy();
	Transform transform;

	static std::vector<GameObject*> gameObjects;
	static GameObject *find(std::string name);
	static void cleanUpObjects();

	vec3 TerrainOffset = vec3(0);
};

template<class T>
T *GameObject::getComponent()
{
	bool found = false;
	T *component = nullptr;
	int i = 0;

	while (!found) {

		//Checks if we have found Component
		if (component = dynamic_cast<T*>(components[i]))
			found = true;

		i++;
		//Reached the end
		if (i == components.size())
			found = true;
	}
	return component;
}

