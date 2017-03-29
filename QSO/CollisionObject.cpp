#include "CollisionObject.h"



CollisionObject::CollisionObject() : Component("")
{
}

CollisionObject::CollisionObject(vec3 halfExtents, bool isStatic, vec3 offset) : Component("")
{
	CollisionManager *manager = CollisionManager::getManager();
	CollisionObject::halfExtents = halfExtents;
	CollisionObject::isStatic = isStatic;
	CollisionObject::offset = offset;
	position = vec3(0);

	manager->addCollisionObjects(this);
}


CollisionObject::~CollisionObject()
{
}
