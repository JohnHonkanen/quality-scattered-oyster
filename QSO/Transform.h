#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\matrix_decompose.hpp>
#include <glm\gtc\quaternion.hpp>
#include <iostream>
#define DEG_TO_RAD 0.0174533

using namespace std;
using namespace glm;
class Transform
{
public:
	Transform();
	virtual ~Transform();
	void setPosition(vec3 position);
	void translate(float x, float y, float z);
	void translate(vec3 translation);
	void rotate(float angle, vec3 axis, bool inRadians = true);
	void rotate(float angle, float ax, float ay, float az, bool inRadians = true);
	void scale(float scale);
	void scale(float scaleX, float scaleY, float scaleZ);
	void scale(vec3 scale);
	void setTransform(mat4 matrix);
	mat4 calculateModelMatrix();
	mat4 get();
	vec3 getPosition();
	void reset();
private:
	mat4 model;
	mat4 translationMatrix;
	mat4 rotationMatrix;
	mat4 scaleMatrix;
};