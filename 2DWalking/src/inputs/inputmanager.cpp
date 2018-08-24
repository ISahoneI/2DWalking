#include "inputmanager.h"

bool InputManager::keys[MAX_KEYS];
bool InputManager::mouseButtons[MAX_MBUTTONS];
double InputManager::mousePosX;
double InputManager::mousePosY;
double InputManager::scrollX;
double InputManager::scrollY;

bool InputManager::inputKeys[MAX_KEYS];
bool InputManager::inputMouseButtons[MAX_MBUTTONS];

InputManager::InputManager()
{
	setAllKeys(false);
	setAllMouseButtons(false);
	mousePosX = 0, mousePosY = 0;
	scrollX = 0, scrollY = 0;
}
InputManager::~InputManager(){}

bool InputManager::isKeyPressed(unsigned int keycode)
{
	if(keycode >= MAX_KEYS)
		return false;
	return keys[keycode];
}

bool InputManager::isKeyPressedOnce(unsigned int keycode)
{
	if (inputKeys[keycode] == false)
	{
		if (isKeyPressed(keycode))
		{
			inputKeys[keycode] = true;
			return true;
		}
	}
	else
	{
		if (!isKeyPressed(keycode))
		{
			inputKeys[keycode] = false;
			return false;
		}
	}
	return false;
}

bool InputManager::isMouseButtonPressed(unsigned int buttoncode)
{
	if (buttoncode >= MAX_MBUTTONS)
		return false;
	return mouseButtons[buttoncode];
}

bool InputManager::isMouseButtonPressedOnce(unsigned int buttoncode)
{
	if (inputMouseButtons[buttoncode] == false)
	{
		if (isMouseButtonPressed(buttoncode))
		{
			inputMouseButtons[buttoncode] = true;
			return true;
		}
	}
	else
	{
		if (!isMouseButtonPressed(buttoncode))
		{
			inputMouseButtons[buttoncode] = false;
			return false;
		}
	}
	return false;
}

void InputManager::setKey(int keycode, bool val)
{
	keys[keycode] = val;
}

void InputManager::setAllKeys(bool val)
{
	for (int i = 0; i < MAX_KEYS; i++)
	{
		keys[i] = val;
		inputKeys[i] = false;
	}
}

void InputManager::setMouseButton(int buttoncode, bool val)
{
	mouseButtons[buttoncode] = val;
}

void InputManager::setAllMouseButtons(bool val)
{
	for (int i = 0; i < MAX_MBUTTONS; i++)
	{
		mouseButtons[i] = val;
		inputMouseButtons[i] = false;
	}
}

void InputManager::setScroll(double xoffset, double yoffset)
{
	this->scrollX = xoffset;
	this->scrollY = yoffset;
}

double InputManager::getScrollYOffset()
{
	double yoffset = InputManager::scrollY;
	InputManager::scrollY = 0;
	return yoffset;
}

void InputManager::getMousePosition(double& x, double& y)
{
	x = InputManager::getMousePosX();
	y = InputManager::getMousePosY();
}