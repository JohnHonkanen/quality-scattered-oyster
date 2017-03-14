#pragma once
#include <string>
#include "Transform.h"
#include "Renderer.h"

class GraphicsHandler
{
protected:
	Renderer *renderer;
public:
	virtual void init() = 0;
	virtual void start() = 0;
	virtual void end() = 0;
	virtual void destroy() = 0;
	virtual void draw() = 0;

	void setRenderer(Renderer *renderer);

};

