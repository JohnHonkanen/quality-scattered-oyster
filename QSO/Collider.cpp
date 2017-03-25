#include "Collider.h"



Collider::Collider():Component("Collider")
{
}

Collider::Collider(string name, ColliderShape shape, float param1, float param2, float param3): Component(name)
{
	setShape(shape, param1,param2,param3);
}


Collider::~Collider()
{
}

void Collider::setShape(ColliderShape shape, float param1, float param2, float param3)
{
	switch (shape)
	{
	case SPHERE:
		colliderShape = new btSphereShape(param1);
		break;
	case BOX:
		colliderShape = new btBoxShape(btVector3(param1, param2, param3));
		break;
	case HEIGHTFIELD_TERRAIN:
		break;
	case STATIC_PLANE:
		break;
	default:
		break;
	}
}

btCollisionShape * Collider::getShape()
{
	return colliderShape;
}

void Collider::destroy()
{
	delete colliderShape;
}
