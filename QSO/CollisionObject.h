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
	CollisionObject(vec3 halfExtents);
	~CollisionObject();
	
	vec3 position;
	ContactManifold manifold;
	vec3 halfExtents;
};

