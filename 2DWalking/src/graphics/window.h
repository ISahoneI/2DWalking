#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../inputs/input.h"


class Window
{
private:
	const char *title;
	int width, height;
	bool is_closed;
	GLFWwindow *window;
	InputManager *inputManager;

public:
	Window(const char *title, int width, int height);
	~Window();
	void clear();
	void update();
	bool closed();

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	bool init();
};