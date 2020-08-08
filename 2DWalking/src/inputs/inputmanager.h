#pragma once

#include <iostream>

#define GAMEPAD_BUTTON_A 0
#define GAMEPAD_BUTTON_B 1
#define GAMEPAD_BUTTON_X 2
#define GAMEPAD_BUTTON_Y 3
#define GAMEPAD_BUTTON_LB 4
#define GAMEPAD_BUTTON_RB 5
#define GAMEPAD_BUTTON_SELECT 6
#define GAMEPAD_BUTTON_START 7
#define GAMEPAD_BUTTON_L3 8
#define GAMEPAD_BUTTON_R3 9
#define GAMEPAD_BUTTON_DPAD_UP 10
#define GAMEPAD_BUTTON_DPAD_RIGHT 11
#define GAMEPAD_BUTTON_DPAD_DOWN 12
#define GAMEPAD_BUTTON_DPAD_LEFT 13

#define GAMEPAD_JOYSTICK_LEFT_X 0
#define GAMEPAD_JOYSTICK_LEFT_Y 1
#define GAMEPAD_JOYSTICK_RIGHT_X 2
#define GAMEPAD_JOYSTICK_RIGHT_Y 3
#define GAMEPAD_TRIGGERS_L 4
#define GAMEPAD_TRIGGERS_R 5

#define MAX_KEYS	 1024
#define MAX_MBUTTONS 32
#define MAX_GBUTTONS 16
#define MAX_GAXES 8

class InputManager
{
private:
	static bool keys[MAX_KEYS];

	static bool mouseButtons[MAX_MBUTTONS];
	static double mousePosX, mousePosY;
	static double scrollX, scrollY;

	static std::string gamepadName;
	static bool gamepadButtons[MAX_GBUTTONS];
	static float gamepadAxes[MAX_GAXES];

	static bool inputKeys[MAX_KEYS];
	static bool inputMouseButtons[MAX_MBUTTONS];
	static bool inputGamepadButtons[MAX_GBUTTONS];

public:
	InputManager();
	~InputManager();

	static bool isKeyPressed(unsigned int keycode);
	static bool isKeyPressedOnce(unsigned int keycode);
	static bool isMouseButtonPressed(unsigned int buttoncode);
	static bool isMouseButtonPressedOnce(unsigned int buttoncode);
	static bool isGamepadButtonPressed(unsigned int buttoncode);
	static bool isGamepadButtonPressedOnce(unsigned int buttoncode);
	static float gamepadJoystickValue(unsigned int axesCode);
	static std::string getGamepadName();

	void setKey(int keycode, bool val);
	void setAllKeys(bool val);
	void setMouseButton(int buttoncode, bool val);
	void setAllMouseButtons(bool val);

	void setGamepad(const char* gamepadName, const float* joysticks, const int axesNumber, const bool* buttons, const int numberOfButtons);
	void setGamepadButton(int buttoncode, bool val);
	void setAllGamepadButtons(bool val);
	void setAllGamepadAxes(float val);


	void setScroll(double xoffset, double yoffset);
	static void getMousePosition(double& x, double& y);

	static double getScrollYOffset();
	static double getMousePosX() { return mousePosX; }
	static double getMousePosY() { return mousePosY; }
	void setMousePosX(double val) { mousePosX = val; }
	void setMousePosY(double val) { mousePosY = val; }


};
