#include "Collider.h"



Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::setShape(btCollisionShape * shape)
{
	colliderShape = shape;
}