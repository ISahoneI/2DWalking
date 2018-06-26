#include "window.h"

Window::Window(const char * title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->inputManager = new InputManager();
	if (!init())
		glfwTerminate();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
	glfwPollEvents();
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapBuffers(window);
}

bool Window::closed()
{
	return glfwWindowShouldClose(window) == 1;
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW!" << std::endl;
		return false;
	}
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to create the GLFW window!" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << std::endl;
		return false;
	}
	std::cout << "Running OpenGL " << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::window_size_callback(GLFWwindow * window, int width, int height)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->width = width;
	win->height = height;
	glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->getInputManager()->setKey(key, action != GLFW_RELEASE);
}

void Window::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->getInputManager()->setMouseButton(button, action != GLFW_RELEASE);
}



void Window::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->getInputManager()->setMousePosX(xpos);
	win->getInputManager()->setMousePosY(ypos);
}
