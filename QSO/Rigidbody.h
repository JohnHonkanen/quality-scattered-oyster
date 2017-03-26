#pragma once
#include <btBulletDynamicsCommon.h>
#include "Component.h"
#include "GameObject.h"

class PhysicsWorld;
class RigidBody : public Component
{
private:
	bool hasInertia;
	btMotionState *state;
	btScalar mass;
	btVector3 inertia;
	btTransform transform;
	PhysicsWorld* world;
public:
	RigidBody();
	RigidBody(string name, PhysicsWorld *world, float mass, vec3 cmass, bool hasInertia = false);
	~RigidBody();
	void init();
	void addMotionState(vec3 cmass);
	void setMass(float mass);
	void calculateLocalInertia();
	void applyCentralForce(vec3 force);
	void applyCentralImpulse(vec3 force);
	void setLinearVelocity(vec3 force);
	vec3 getLinearVelocity();
	btTransform getMotionState();
	void updateStep();
	void destroy();

	btRigidBody *rigidbody;

	//Helper Functions
	btVector3 convertTobtVector3(vec3 vec);
	vec3 convertToVec3(btVector3 vec);
};
