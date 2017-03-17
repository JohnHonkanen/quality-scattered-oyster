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

void MouseInput::setLastPosition(vec2 position)
{
	MouseInput::lastPosition = position;
}

vec2 MouseInput::getPosition()
{
	return MouseInput::position;
}

vec2 MouseInput::getLastPosition()
{
	return MouseInput::lastPosition;
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

void MouseInput::setLastScrollOffset(vec2 scrollOffset)
{
	MouseInput::lastScrollOffset = scrollOffset;
}

vec2 MouseInput::getScrollOffset()
{
	return MouseInput::scrollOffset;
}

vec2 MouseInput::getLastScrollOffset()
{
	return MouseInput::lastScrollOffset;
}
