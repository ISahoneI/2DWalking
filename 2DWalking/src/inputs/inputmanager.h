#pragma once

#include <iostream>

#define MAX_KEYS	 1024
#define MAX_MBUTTONS 32

class InputManager
{
private:
	static bool keys[MAX_KEYS];
	static bool mouseButtons[MAX_MBUTTONS];
	static double mousePosX, mousePosY;
	static double scrollX, scrollY;

	static bool inputKeys[MAX_KEYS];
	static bool inputMouseButtons[MAX_MBUTTONS];

public:
	InputManager();
	~InputManager();

	static bool isKeyPressed(unsigned int keycode);
	static bool isKeyPressedOnce(unsigned int keycode);
	static bool isMouseButtonPressed(unsigned int buttoncode);
	static bool isMouseButtonPressedOnce(unsigned int buttoncode);

	void setKey(int keycode, bool val);
	void setAllKeys(bool val);
	void setMouseButton(int buttoncode, bool val);
	void setAllMouseButtons(bool val);

	void setScroll(double xoffset, double yoffset);
	static void getMousePosition(double& x, double& y);

	static double getScrollYOffset();
	 static double getMousePosX() { return mousePosX; }
	 static double getMousePosY() { return mousePosY; }
	 void setMousePosX(double val) { mousePosX = val; }
	 void setMousePosY(double val) { mousePosY = val; }
};
