#include "RigidBody.h"
#include "Collider.h"
#include "PhysicsWorld.h"
#include <glm\gtc\type_ptr.hpp>
#include "Terrain.h";

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
	rigidbody->setAngularFactor(btVector3(0,0,0));
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

void RigidBody::setLinearVelocity(vec3 force)
{
	rigidbody->setLinearVelocity(convertTobtVector3(force));
}

vec3 RigidBody::getLinearVelocity()
{
	return convertToVec3(rigidbody->getLinearVelocity());
}

btTransform RigidBody::getMotionState()
{
	btTransform btTrans;
	rigidbody->getMotionState()->getWorldTransform(btTrans);
	return btTrans;
}

void RigidBody::updateStep()
{
	btTransform trans = getMotionState();
	mat4 motion;
	trans.getOpenGLMatrix(value_ptr(motion));
	vec3 pos = motion[3];
	GameObject *terrain = GameObject::find("terrain");
	Terrain *terrainShape = terrain->getComponent<Terrain>();
	mapData data = terrainShape->getData();
	float terrainX = pos.x - terrain->transform.physics[3].x;
	float terrainZ = pos.z - terrain->transform.physics[3].y;
	int gridX = (int)floor(terrainX / terrainShape->getGridSize());
	int gridZ = (int)floor(terrainZ / terrainShape->getGridSize());
	if (gridX >= terrainShape->getData().xLength - 1 || gridZ >= terrainShape->getData().zLength - 1 || gridX < 0 || gridZ < 0) {
	}
	else {
		float xCoord = ((int)terrainX % (int)terrainShape->getGridSize())/ (float) terrainShape->getGridSize();
		float zCoord = ((int)terrainZ % (int)terrainShape->getGridSize() / (float) terrainShape->getGridSize());
		float trianglePos;
		if (xCoord <= (1 - zCoord)) {
			trianglePos = barryCentric(vec3(0, data.heightmap[gridX][gridZ], 0),vec3(1, data.heightmap[gridX + 1][gridZ], 0), vec3(0, data.heightmap[gridX][gridZ + 1], 1), vec2(xCoord, zCoord));
		}
		else {
			trianglePos = barryCentric(vec3(1, data.heightmap[gridX + 1][gridZ], 0), vec3(1,data.heightmap[gridX + 1][gridZ + 1], 1), vec3(0,data.heightmap[gridX][gridZ + 1], 1), vec2(xCoord, zCoord));
		}
		printf("Terrain thing %i, %i Height: %f \n", gridX, gridZ, data.heightmap[gridX][gridZ]);
		if (pos.y < trianglePos) {
				motion[3].y = trianglePos;
		}
	}
	gameObject->transform.physics = motion;

}

void RigidBody::destroy()
{
	delete rigidbody;
}