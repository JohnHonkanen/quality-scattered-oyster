#pragma once
#include "Component.h"
#include "btBulletDynamicsCommon.h"

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
	~Collider();

	void setShape(btCollisionShape * shape);
};
