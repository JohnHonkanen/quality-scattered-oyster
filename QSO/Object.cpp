#include "Object.h"

int Object::instance_id;

Object::Object()
{
	Object::instance_id++;
}


Object::~Object()
{
}

void Object::destroy()
{
	delete this;
}

string Object::toString()
{
	return Object::name;
}

int Object::getInstancedID()
{
	return Object::instance_id;
}

string Object::getName()
{
	return name;
}

void Object::Destroy(Object * obj)
{
	obj->destroy();
}
