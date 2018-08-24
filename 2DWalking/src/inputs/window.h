#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../inputs/inputmanager.h"


class Window
{
private:
	const char *title;
	int width, height;
	bool is_closed, is_fullscreen;
	GLFWwindow *window;
	InputManager *inputManager;
public:
	Window(const char *title, int width, int height, bool is_fullscreen);
	~Window();
	void update();
	void clear();
	void close();
	bool closed();

	void getDimension(int& width, int& height);
	 int getWidth() const { return width; }
	 int getHeight() const { return height; }
	 InputManager* getInputManager() const{ return inputManager; }

	//Callbacks
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
private:
	bool init();
};