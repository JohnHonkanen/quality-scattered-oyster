#include "RigidBody.h"
#include "Collider.h"


btVector3 RigidBody::convertTobtVector3(vec3 vec)
{
	return btVector3(btScalar(vec.x), btScalar(vec.y), (btScalar(vec.z)));
}

RigidBody::RigidBody() :Component("Rigidbody")
{
	RigidBody::mass = 0;
	RigidBody::inertia = btVector3(0, 0, 0);
}


RigidBody::~RigidBody()
{
}

void RigidBody::init()
{
	btCollisionShape * shape = gameObject->getComponent<Collider>()->getShape();
	btRigidBody::btRigidBodyConstructionInfo
		constructionInfo(RigidBody::mass, RigidBody::state, shape, RigidBody::inertia);

	RigidBody::rigidbody = new btRigidBody(constructionInfo);
}

void RigidBody::addGameObject(GameObject * gameObject)
{
	RigidBody::gameObject = gameObject;
}

void RigidBody::addMotionState(btMotionState * state)
{
	RigidBody::state = state;
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

vec3 RigidBody::getMotionState()
{
	btTransform btTrans;
	rigidbody->getMotionState()->getWorldTransform(btTrans);
	printf(" Y Loc: %f\n", btTrans.getOrigin().getY());
	return vec3(btTrans.getOrigin().getX(), btTrans.getOrigin().getY(), btTrans.getOrigin().getZ());
}

void RigidBody::destroy()
{
	delete rigidbody;
}