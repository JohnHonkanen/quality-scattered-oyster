#pragma once
#include <btBulletDynamicsCommon.h>
#include "Component.h"


enum ColliderShape {
	SPHERE = 1,
	BOX = 2,
	CYLINDER = 3,
	CAPSULE = 4,
	CONE = 5,
	CONVEX_HULL = 6,
	CONVEX_TRIANGLE = 7,
	TRIANGLE_MESH = 8,
	HEIGHTFIELD_TERRAIN = 9,
	STATIC_PLANE = 10
};

class Collider : public Component
{
private:
	btCollisionShape *colliderShape;
public:
	Collider();
	Collider(string name, ColliderShape shape, float param1 = 1.0f, float param2 = 1.0f, float param3 = 1.0f);
	~Collider();
	void setShape(ColliderShape shape, float param1 = 1.0f, float param2 = 1.0f, float param3 = 1.0f);
	btCollisionShape *getShape();
	void destroy();
};
