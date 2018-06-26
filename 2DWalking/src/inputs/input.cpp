#include "input.h"

InputManager::InputManager()
{
	setAllKeys(false);
	setAllMouseButtons(false);
	mousePosX = 0;
	mousePosY = 0;
}


InputManager::~InputManager(){}

bool InputManager::IsKeyPressed(unsigned int keycode) const
{
	if(keycode >= MAX_KEYS)
		return false;
	return keys[keycode];
}

bool InputManager::IsMouseButtonPressed(unsigned int buttoncode) const
{
	if (buttoncode >= MAX_MBUTTONS)
		return false;
	return mouseButtons[buttoncode];
}

void InputManager::setKey(int keycode, bool val)
{
	keys[keycode] = val;
}

void InputManager::setMouseButton(int buttoncode, bool val)
{
	mouseButtons[buttoncode] = val;
}

void InputManager::setAllKeys(bool val)
{
	for (int i = 0; i < MAX_KEYS; i++)
		keys[i] = val;
}

void InputManager::setAllMouseButtons(bool val)
{
	for (int i = 0; i < MAX_MBUTTONS; i++)
		mouseButtons[i] = val;
}
