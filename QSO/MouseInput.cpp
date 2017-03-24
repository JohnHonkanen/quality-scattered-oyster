#include "MouseInput.h"
#include <iostream>


MouseInput::MouseInput()
{
	buttonPressed[0] = false;
	buttonPressed[1] = false;
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

bool MouseInput::getButtonPressed(int button)
{
	//if (button != 1 || button != 0) {
	//	return false;
	//}

	return buttonPressed[button];
}

void MouseInput::setButtonPressed(int button, bool pressed)
{
	buttonPressed[button] = pressed;
	printf("mouse button result %i \n", buttonPressed[button]);
	printf("mouse button function result %i \n", getButtonPressed(button));
}
