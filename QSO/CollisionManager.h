#pragma once
#include <vector>
#include "GameObject.h"

class CollisionObject;
class CollisionManager
{
private:
	vector<CollisionObject*> colObjects;
	static CollisionManager *manager;

public:
	CollisionManager();
	~CollisionManager();

	static CollisionManager* getManager();
	void addCollisionObjects(CollisionObject *colObject);
	bool checkCollision(CollisionObject a, CollisionObject b);
	void handleCollision(CollisionObject *a, CollisionObject *b);
	void update();
};

