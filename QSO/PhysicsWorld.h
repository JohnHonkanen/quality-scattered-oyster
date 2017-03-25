#pragma once
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>
#include <glm\glm.hpp>
#include <vector>
#include "btBulletDynamicsCommon.h"
#include "RigidBody.h"


using namespace glm;
class PhysicsWorld
{
private:
	btBroadphaseInterface* _broadphase;
	btDefaultCollisionConfiguration* _collisionConfiguration;
	btCollisionDispatcher* _dispatcher;
	btSequentialImpulseConstraintSolver* _solver;
	btDiscreteDynamicsWorld* _dynamicsWorld;
	vec3 gravity;
	std::vector<RigidBody*> bodies;
public:
	PhysicsWorld();
	~PhysicsWorld();
	void setGravity(vec3 gravity);
	void addRigidBody(RigidBody *body);
	void removeRigidBody(RigidBody *body);
	void stepSimulation(float deltaTime, int maxSubSteps);
	void destroy();
};
