#pragma once
#include <vector>
#include "Object.h"
#include "GameBehaviour.h"
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
	void broadcastMessage(GameBehaviour::BehaviorFuncs func);
	template<class T>
	T *getComponent();
	void addComponent(Component* component);
	void destroy();
	Transform transform;

	static std::vector<GameObject*> gameObjects;
	static GameObject *find(std::string name);
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

