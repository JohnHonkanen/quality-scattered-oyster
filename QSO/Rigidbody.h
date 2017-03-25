#pragma once
#include <btBulletDynamicsCommon.h>
#include "Component.h"
#include "GameObject.h"
class RigidBody : public Component
{
private:
	GameObject *gameObject;
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
	void addGameObject(GameObject *gameObject);
	void addMotionState(btMotionState *state);
	void setMass(float mass);
	void calculateLocalInertia();
	void applyCentralForce(vec3 force);
	void applyCentralImpulse(vec3 force);
	vec3 getMotionState();
	void destroy();

	btRigidBody *rigidbody;
};
