#include "RigidBody.h"
#include "Collider.h"
#include "PhysicsWorld.h"
#include <glm\gtc\type_ptr.hpp>

btVector3 RigidBody::convertTobtVector3(vec3 vec)
{
	return btVector3(btScalar(vec.x), btScalar(vec.y), (btScalar(vec.z)));
}

vec3 RigidBody::convertToVec3(btVector3 vec)
{
	return vec3(vec.x(),vec.y(), vec.z());
}

RigidBody::RigidBody() :Component("Rigidbody")
{
	RigidBody::mass = 0;
	RigidBody::inertia = btVector3(0, 0, 0);
}

RigidBody::RigidBody(string name, PhysicsWorld *world, float mass, vec3 cmass, bool hasInertia):Component(name)
{
	setMass(mass);
	addMotionState(cmass);
	RigidBody::hasInertia = hasInertia;

	RigidBody::world = world;
}


RigidBody::~RigidBody()
{
}

void RigidBody::init()
{
	btCollisionShape * shape = gameObject->getComponent<Collider>()->getShape();
	if (shape != nullptr) {
		if (hasInertia)
			calculateLocalInertia();
	}
	
	btRigidBody::btRigidBodyConstructionInfo
		constructionInfo(RigidBody::mass, RigidBody::state, shape, RigidBody::inertia);

	RigidBody::rigidbody = new btRigidBody(constructionInfo);
	RigidBody::world->addRigidBody(this);
}

void RigidBody::addMotionState(vec3 cmass)
{
	RigidBody::state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(cmass.x, cmass.y, cmass.z)));
}

void RigidBody::setMass(float mass)
{
	RigidBody::mass = mass;
}

void RigidBody::calculateLocalInertia()
{
	btCollisionShape * shape = gameObject->getComponent<Collider>()->getShape();
	if (shape != nullptr) {
		shape->calculateLocalInertia(btScalar(RigidBody::mass), RigidBody::inertia);
	}
}

void RigidBody::applyCentralForce(vec3 force)
{
	RigidBody::rigidbody->applyCentralForce(convertTobtVector3(force));
}

void RigidBody::applyCentralImpulse(vec3 force)
{
	RigidBody::rigidbody->applyCentralImpulse(convertTobtVector3(force));
}

btTransform RigidBody::getMotionState()
{
	btTransform btTrans;
	rigidbody->getMotionState()->getWorldTransform(btTrans);
	return btTrans;
}

void RigidBody::updateStep()
{
	mat4 motion;
	getMotionState().getOpenGLMatrix(value_ptr(motion));
	gameObject->transform.setPosition(motion[3]);
}

void RigidBody::destroy()
{
	delete rigidbody;
}