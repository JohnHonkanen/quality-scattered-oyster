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
	RigidBody(string name, PhysicsWorld *world, float mass, vec3 cmass, btQuaternion orientation, bool hasInertia = false);
	~RigidBody();
	void init();
	void addMotionState(vec3 cmass, btQuaternion orientation = btQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
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

static float barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos) {
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
