#pragma once
#include <glm\glm.hpp>

#include "Component.h"
#include "CollisionManager.h"

using namespace glm;

struct ContactManifold {
	vector<vec3> contacts;
};
class CollisionObject :
	public Component
{
private:
	
	
public:
	CollisionObject();
	CollisionObject(vec3 halfExtents, bool isStatic = false, vec3 offset = vec3(0));
	~CollisionObject();
	
	vec3 position;
	ContactManifold manifold;
	vec3 halfExtents;
	bool colliding = false;
	vec3 contactNormal;
	vec3 offset;
	bool isStatic;
	CollisionObject *collidingObject;
};

