#pragma once
#include <btBulletDynamicsCommon.h>
#include "Component.h"
#include "GameObject.h"
class RigidBody : public Component
{
private:
	btMotionState *state;
	btScalar mass;
	btVector3 inertia;
	btTransform transform;

	//Helper Functions
	btVector3 convertTobtVector3(vec3 vec);
	vec3 convertToVec3(btVector3 vec);
public:
	RigidBody();
	RigidBody(string name, float mass, vec3 cmass, bool hasInertia = false);
	~RigidBody();
	void init();
	void addMotionState(vec3 cmass);
	void setMass(float mass);
	void calculateLocalInertia();
	void applyCentralForce(vec3 force);
	void applyCentralImpulse(vec3 force);
	vec3 getMotionState();
	void updateStep();
	void destroy();

	btRigidBody *rigidbody;
};
