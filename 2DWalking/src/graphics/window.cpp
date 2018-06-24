#include "window.h"

Window::Window(const char * title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;
	if (!init())
		glfwTerminate();
	inputManager = new InputManager();
	glfwSetKeyCallback(window, InputManager::key_callback);
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
	glViewport(0, 0, width, height);
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

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << std::endl;
		return false;
	}

	std::cout << "Running OpenGL " << glGetString(GL_VERSION) << std::endl;
	return true;
}
