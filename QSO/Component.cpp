#include "Component.h"
#include "GameObject.h"
#include "Transform.h"


Component::Component(std::string name)
{
	Object::name = name;
}


Component::~Component()
{
}

void Component::init()
{
}

void Component::setGameObject(GameObject * gameObject)
{
	Component::gameObject = gameObject;
}
