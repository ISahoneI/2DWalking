#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS	 1024
#define MAX_MBUTTONS 32

class InputManager
{
private:
	

	bool keys[MAX_KEYS];
	bool mouseButtons[MAX_MBUTTONS];
	double mousePosX, mousePosY;

public:
	InputManager();
	~InputManager();

	bool IsKeyPressed(int keycode) const;
	bool IsMouseButtonPressed(int buttoncode) const;

	void setKeys(bool val);
	void setMouseButtons(bool val);

	inline double getMousePosX() const { return mousePosX; }
	inline double getMousePosY() const { return mousePosY; }


	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

