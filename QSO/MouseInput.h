#pragma once

#include <glm\glm.hpp>

using namespace glm;

class MouseInput
{
private:
	vec2 position;
	vec2 offSet;
	vec2 scrollOffset;
public:
	MouseInput();
	~MouseInput();

	void setPosition(vec2 position);
	vec2 getPosition();
	void setOffset(vec2 offSet);
	vec2 getOffset();
	void setScrollOffset(vec2 offSet);
	vec2 getScrollOffset();
};

