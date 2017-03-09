#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

std::vector<GameObject*> GameObject::gameObjects;

GameObject::GameObject(std::string name)
{
	Object::name = name;
	GameObject::gameObjects.push_back(this);
}


GameObject::~GameObject()
{
}
void GameObject::broadcastMessage(GameBehaviour::BehaviorFuncs func)
{
	//Go Through our Components
	for (int i = 0; i <  GameObject::components.size(); i++) {

		GameBehaviour *behaviour = dynamic_cast<GameBehaviour*>(GameObject::components[i]);
		if (behaviour) {
			switch (func) {
			case GameBehaviour::BH_START:
				behaviour->Start();
				break;
			case GameBehaviour::BH_UPDATE:
				behaviour->Update();
				break;
			case GameBehaviour::BH_VISIBLE:
				behaviour->onBecomeVisible();
				break;
			case GameBehaviour::BH_INVISIBLE:
				behaviour->onBecomeVisible();
				break;
			default:
				/*Throw Error Later*/
				break;
			}
		}
		if (GameObject::components[i]->gameObject)
			GameObject::components[i]->gameObject->broadcastMessage(func);

	}
}

void GameObject::addComponent(Component * component)
{
	GameObject::components.push_back(component);
}

void GameObject::destroy()
{
	//Search and Remove from list
	bool found = false;
	int i = 0;
	int index = -1;
	while (!found) {
		//Checks if we have found Component
		if (GameObject::gameObjects[i]->name == GameObject::name) {
			found = true;
			index = i;
		}
		i++;
		//Reached the end
		if (i == GameObject::gameObjects.size())
			found = true;
	}
	//Remove from the gameObject list
	if (index != -1 && index < GameObject::gameObjects.size()) {
		GameObject::gameObjects[index] = GameObject::gameObjects.back();
		GameObject::gameObjects.pop_back();
	}

	//Clear Components
	for (int i = 0; i < components.size(); i++) {
		components[i]->destroy();
	}

	delete this;
}

GameObject *GameObject::find(std::string name)
{
	bool found = false;
	GameObject* obj = nullptr;
	int i = 0;
	while (!found) {

		//Checks if we have found Component
		if (GameObject::gameObjects[i]->name == name) {
			found = true;
			obj = GameObject::gameObjects[i];
		}
			

		i++;
		//Reached the end
		if (i == GameObject::gameObjects.size())
			found = true;
	}
	return obj;
}

template<class T>
T *GameObject::getComponent()
{
	bool found = false;
	T *component = nullptr;
	int i = 0;

	while (!found) {

		//Checks if we have found Component
		if (component = dynamic_cast<T>(components[i]))
			found = true;

		i++;
		//Reached the end
		if (i == components.size())
			found = true;
	}
	return component;
}