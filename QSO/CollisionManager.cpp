#include "CollisionManager.h"
#include "CollisionObject.h"

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
	vec3 box1 = a.position;
	vec3 box2 = a.position;

	vec3 box1Min = a.position - a.halfExtents;
	vec3 box1Max = a.position + a.halfExtents;

	vec3 box2Min = b.position - b.halfExtents;
	vec3 box2Max = b.position + b.halfExtents;
	
	return (box1Min.x <= box2Max.x && box1Max.x >= box2Min.x) &&
		(box1Min.y <= box2Max.y && box1Max.y >= box2Min.y) &&
		(box1Min.z <= box2Max.z && box1Max.z >= box2Min.z);
}

void CollisionManager::update()
{
	for (int i = 0; i < colObjects.size(); i++) {
		CollisionObject *iObjs = colObjects.at(i);
		GameObject *object = iObjs->gameObject;

		iObjs->position = object->transform.physics[3];
	}

	//To Be filled in
	for (int i = 0; i < colObjects.size(); i++) {
		CollisionObject *iObjs = colObjects.at(i);
		for (int k = i + 1; k < colObjects.size(); k++) {
			CollisionObject *kObjs = colObjects.at(k);

			if (checkCollision(*iObjs, *kObjs))
				printf("Colliding \n");
		}
	}
}
