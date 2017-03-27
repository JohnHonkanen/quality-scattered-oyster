#include "Transform.h"



Transform::Transform()
{
	Transform::model = mat4(1.0f);
}


Transform::~Transform()
{
}
/*
Sets the position to a specified amount
@param vec3 position to be set
*/
void Transform::setPosition(vec3 position)
{

	Transform::translationMatrix[3] = vec4(position, 1.0f);
}
/*
Translates our Matrix
@param x x-value to translate
@param y y-value to translate
@param z z-value to translate
*/
void Transform::translate(float x, float y, float z)
{
	vec3 translation(x, y, z);
	translate(translation);
}
/*
Translates our Matrix
@param translation vec3 to translate
*/
void Transform::translate(vec3 translation)
{
	Transform::translationMatrix = glm::translate(Transform::translationMatrix, translation);
}

/*
Rotates our Matrix
@param angle angle in radians to rotate
@param axis orientation to rotate
*/

void Transform::rotate(float angle, vec3 axis, bool inRadians)
{
	if (!inRadians) {
		angle *= DEG_TO_RAD;
	}

	if (axis.x > 0) {
		rotation.x += angle / axis.x;
	}

	if (axis.y > 0) {
		rotation.y += angle / axis.y;
	}

	if (axis.z > 0) {
		rotation.z += angle / axis.z;
	}

	Transform::rotationMatrix = glm::rotate(Transform::rotationMatrix, angle, axis);

}
/*
Rotates our Matrix
@param angle angle in radians to rotate
@param ax x-orientation to rotate
@param ay y-orientation to rotate
@param az z-orientation to rotate
*/

void Transform::rotate(float angle, float ax, float ay, float az, bool inRadians)
{
	if (!inRadians)
		angle *= DEG_TO_RAD;

	vec3 axis(ax, ay, az);
	rotate(angle, axis);
}
/*
Scales our Matrix uniformly in all direction
@param s Scalar amount
*/
void Transform::scale(float s)
{
	vec3 scaleVec(s);
	scale(scaleVec);
}
/*
Scales our Matrix
@param sx Scalar X amount
@param sy Scalar Y amount
@param sz Scalar Z amount
*/
void Transform::scale(float sx, float sy, float sz)
{
	vec3 scaleVec(sx, sy, sz);
	scale(scaleVec);
}
/*
Scales our Matrix
@param sx vector3 with scalar values
*/
void Transform::scale(vec3 scale)
{
	Transform::scaleMatrix = glm::scale(Transform::scaleMatrix, scale);
}

void Transform::setTransform(mat4 matrix)
{
	Transform::model = matrix;
}
void Transform::setTranslationMatrix(mat4 matrix)
{
	translationMatrix = matrix;
}
void Transform::addTranslationMatrix(mat4 matrix)
{
	translationMatrix += matrix;
}
mat4 Transform::calculateModelMatrix()
{
	//Transform::model = Transform::translationMatrix * Transform::rotationMatrix ;
	Transform::model = physics * Transform::scaleMatrix;
	return Transform::model;
}
/*
Gets our mat4 matrix
*/
mat4 Transform::get()
{
	return Transform::model;
}
vec3 Transform::getPosition()
{
	return Transform::physics[3];
}
vec3 Transform::getRotation()
{
	return rotation;
}
/*
Resets to identity matrix
*/
void Transform::reset()
{
	Transform::model = mat4();
}

