#pragma once
#include "Component.h"
#include "Collider.h"
#include "btBulletDynamicsCommon.h"
class RigidBody : public Component
{
private:
	btCollisionShape *collider;
	btMotionState *state;
	btScalar mass;
	btVector3 inertia;
	btTransform transform;

	//Helper Functions
	btVector3 convertTobtVector3(vec3 vec);
public:
	RigidBody();
	~RigidBody();
	void init();
	void addCollider(btCollisionShape *collider);
	void addMotionState(btMotionState *state);
	void setMass(float mass);
	void calculateLocalInertia();
	void applyCentralForce(vec3 force);
	void applyCentralImpulse(vec3 force);
	vec3 getMotionState();
	void destroy();

	btRigidBody *rigidbody;
};
