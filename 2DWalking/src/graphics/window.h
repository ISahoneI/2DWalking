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
	inline InputManager* getInputManager() const{ return inputManager; }

	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
private:
	bool init();
};