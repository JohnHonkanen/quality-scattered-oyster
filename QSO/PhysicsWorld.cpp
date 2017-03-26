#include "PhysicsWorld.h"



PhysicsWorld::PhysicsWorld()
{
	_broadphase = new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(_dispatcher);
	_solver = new btSequentialImpulseConstraintSolver;
	_dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
	_dynamicsWorld->setGravity(btVector3(0, -10, 0));
}


PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::setGravity(vec3 gravity)
{
	PhysicsWorld::gravity = gravity;
	_dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}

void PhysicsWorld::addRigidBody(RigidBody * body)
{
	_dynamicsWorld->addRigidBody(body->rigidbody);
	bodies.push_back(body);
}

void PhysicsWorld::removeRigidBody(RigidBody * body)
{
	_dynamicsWorld->removeRigidBody(body->rigidbody);
}

void PhysicsWorld::stepSimulation(float deltaTime, int maxSubSteps)
{
	//printf("Stepping Sim %f \n", deltaTime);
	_dynamicsWorld->stepSimulation(btScalar(deltaTime), maxSubSteps);
	for (int i = 0; i < bodies.size(); i++) {
		bodies[i]->updateStep();
	}
}

void PhysicsWorld::destroy()
{
	for (int i = 0; i < bodies.size(); i++) {
		_dynamicsWorld->removeRigidBody(bodies[i]->rigidbody);
	}
	delete _dynamicsWorld;
	delete _solver;
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _broadphase;
	
}