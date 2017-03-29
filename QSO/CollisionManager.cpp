#include "CollisionManager.h"
#include "CollisionObject.h"
#include "Utils.h"
#include "Rigidbody.h"

CollisionManager *CollisionManager::manager = nullptr;

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

CollisionManager *CollisionManager::getManager()
{
	if (CollisionManager::manager == nullptr)
		CollisionManager::manager = new CollisionManager();

	return CollisionManager::manager;

}

void CollisionManager::addCollisionObjects(CollisionObject * colObject)
{
	colObjects.push_back(colObject);
}

bool CollisionManager::checkCollision(CollisionObject a, CollisionObject b)
{

	vec3 box1Min = a.position - a.halfExtents;
	vec3 box1Max = a.position + a.halfExtents;

	vec3 box2Min = b.position - b.halfExtents;
	vec3 box2Max = b.position + b.halfExtents;
	
	return (box1Min.x <= box2Max.x && box1Max.x >= box2Min.x) &&
		(box1Min.y <= box2Max.y && box1Max.y >= box2Min.y) &&
		(box1Min.z <= box2Max.z && box1Max.z >= box2Min.z);
}

void CollisionManager::handleCollision(CollisionObject *a, CollisionObject *b)
{
	a->colliding = true;
	b->colliding = true;

	vec3 box1Min = a->position - a->halfExtents;
	vec3 box1Max = a->position + a->halfExtents;

	vec3 box2Min = b->position - b->halfExtents;
	vec3 box2Max = b->position + b->halfExtents;

	vec3 normal = Utils::getAABBFaceNormal(a->position, b);
	
	a->contactNormal = normal;
	b->contactNormal = -normal;
	a->collidingObject = b;
	b->collidingObject = a;

	RigidBody *aRigidbody = a->gameObject->getComponent<RigidBody>();
	RigidBody *bRigidbody = b->gameObject->getComponent<RigidBody>();
	
	vec3 norm = normal;
	btVector3 velocity = aRigidbody->rigidbody->getLinearVelocity();

	if (norm.x > 0 || norm.x < 0) {
		velocity.setX(norm.x);
	}

	if (norm.y > 0 || norm.y < 0) {
		velocity.setY(norm.y);
	}

	if (norm.z > 0 || norm.z < 0) {
		velocity.setZ(norm.z);
	}

	if(!a->isStatic)
		aRigidbody->rigidbody->setLinearVelocity(velocity);
	if(!b->isStatic)
		bRigidbody->rigidbody->setLinearVelocity(-velocity);
}

void CollisionManager::update()
{
	for (int i = 0; i < colObjects.size(); i++) {
		CollisionObject *iObjs = colObjects.at(i);
		GameObject *object = iObjs->gameObject;

		iObjs->colliding = false;
		iObjs->position = vec3(object->transform.physics[3]) + iObjs->offset;

	}

	//To Be filled in
	for (int i = 0; i < colObjects.size(); i++) {
		CollisionObject *iObjs = colObjects.at(i);
		for (int k = i + 1; k < colObjects.size(); k++) {
			CollisionObject *kObjs = colObjects.at(k);

			if (checkCollision(*iObjs, *kObjs))
				handleCollision(iObjs, kObjs);
		}
	}
}
