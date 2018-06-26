#pragma once

#include <iostream>

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

	bool IsKeyPressed(unsigned int keycode) const;
	bool IsMouseButtonPressed(unsigned int buttoncode) const;


	void setKey(int keycode, bool val);
	void setMouseButton(int buttoncode, bool val);
	void setAllKeys(bool val);
	void setAllMouseButtons(bool val);

	inline double getMousePosX() const { return mousePosX; }
	inline double getMousePosY() const { return mousePosY; }
	inline void setMousePosX(double val) { mousePosX = val; }
	inline void setMousePosY(double val) { mousePosY = val; }

};

