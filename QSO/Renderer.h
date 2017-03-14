#pragma once

#include <GL\glew.h>
#include "Transform.h"

class Renderer //Rendering Strategy
{
protected:
	Transform view;
	Transform projection;
	float alpha;
public:
	Renderer();
	virtual ~Renderer();

	virtual void renderObject() = 0; // Handles the draw of the object

	void addView(Transform view);
	void addProjection(Transform projection);
	void setAlpha(float alpha);
	float getAlpha();
};

