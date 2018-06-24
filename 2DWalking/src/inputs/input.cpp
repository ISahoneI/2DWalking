#include "input.h"

InputManager::InputManager()
{
	setKeys(false);
	setMouseButtons(false);
}


InputManager::~InputManager()
{
}

bool InputManager::IsKeyPressed(int keycode) const
{
	if(keycode >= MAX_KEYS)
		return false;
	return keys[keycode];
}

bool InputManager::IsMouseButtonPressed(int buttoncode) const
{
	if (buttoncode >= MAX_MBUTTONS)
		return false;
	return keys[buttoncode];
}

void InputManager::setKeys(bool val)
{
	for (int i = 0; i < MAX_KEYS; i++)
		keys[i] = val;
}

void InputManager::setMouseButtons(bool val)
{
	for (int i = 0; i < MAX_MBUTTONS; i++)
		mouseButtons[i] = val;
}

void InputManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//TEST
	static float TEST = 0;
	if (key == GLFW_KEY_E && action == GLFW_REPEAT)
	{
		std::cout << "Touche E pressée" << std::endl;
		glClearColor(TEST, 0.3f, 0.3f, 1.0f);
		TEST += 0.01f;
	}
}
