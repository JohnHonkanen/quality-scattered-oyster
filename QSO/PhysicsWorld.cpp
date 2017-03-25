#include "PhysicsWorld.h"



PhysicsWorld::PhysicsWorld()
{
	_broadphase = new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(_dispatcher);
	_solver = new btSequentialImpulseConstraintSolver;
	_dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
}


PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::setGravity(vec3 gravity)
{
	gravity = gravity;
	_dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}

void PhysicsWorld::addRigidBody(RigidBody * body)
{
	_dynamicsWorld->addRigidBody(body->rigidbody);
}

void PhysicsWorld::removeRigidBody(RigidBody * body)
{
	_dynamicsWorld->removeRigidBody(body->rigidbody);
}

void PhysicsWorld::stepSimulation(float deltaTime, int maxSubSteps)
{
	//printf("Stepping Sim %f \n", deltaTime);
	_dynamicsWorld->stepSimulation(btScalar(deltaTime), maxSubSteps);
}

void PhysicsWorld::destroy()
{
	delete _broadphase;
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _solver;
	delete _dynamicsWorld;
	delete this;
}