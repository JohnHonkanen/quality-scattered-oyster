#include "MouseInput.h"



MouseInput::MouseInput()
{
}


MouseInput::~MouseInput()
{
}

void MouseInput::setPosition(vec2 position)
{
	MouseInput::position = position;
}

vec2 MouseInput::getPosition()
{
	return MouseInput::position;
}

void MouseInput::setOffset(vec2 offSet)
{
	MouseInput::offSet = offSet;
}

vec2 MouseInput::getOffset()
{
	return MouseInput::offSet;
}

void MouseInput::setScrollOffset(vec2 offSet)
{
	MouseInput::scrollOffset = offSet;
}

vec2 MouseInput::getScrollOffset()
{
	return MouseInput::scrollOffset;
}
