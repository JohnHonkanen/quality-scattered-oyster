#include "KeyboardInput.h"



KeyboardInput::KeyboardInput()
{
	for (int i = 0; i < 1024; i++) {
		KeyboardInput::keys[i] = false;
	}
}


KeyboardInput::~KeyboardInput()
{
}

void KeyboardInput::setKey(int key, bool keyPress)
{
	KeyboardInput::keys[key] = keyPress;
}

bool KeyboardInput::keyPressed(int key)
{
	return keys[key];
}
