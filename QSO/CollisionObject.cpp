#include "CollisionObject.h"



CollisionObject::CollisionObject() : Component("")
{
}

CollisionObject::CollisionObject(vec3 halfExtents) : Component("")
{
	CollisionManager *manager = CollisionManager::getManager();
	CollisionObject::halfExtents = halfExtents;
	position = vec3(0);

	manager->addCollisionObjects(this);
}


CollisionObject::~CollisionObject()
{
}
