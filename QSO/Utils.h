// Marco Gilardi UWS
#pragma once

#include <glm\glm.hpp>

class CollisionObject;

using namespace glm;
class Utils
{
public:
	Utils();
	~Utils();

	static const vec3 up;
	static const vec3 down;
	static const vec3 left;
	static const vec3 right;
	static const vec3 back;
	static const vec3 front;

	static char computePointMask(const vec3& P, const CollisionObject* const aabb);
	static bool pointIsAbovePlane(const vec3& P, const vec3& n, float c);
	static vec3 getAABBFaceNormal(const vec3& P, const CollisionObject* const aabb);
};

