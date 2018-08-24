#include "window.h"

Window::Window(const char * title, int width, int height, bool is_fullscreen)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->is_fullscreen = is_fullscreen;
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

void Window::close()
{
	glfwSetWindowShouldClose(window, true);
}

bool Window::closed()
{
	return glfwWindowShouldClose(window) == 1;
}

void Window::getDimension(int& width, int& height)
{
	width = this->width;
	height = this->height;
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW!" << std::endl;
		return false;
	}
	//window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to create the GLFW window!" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetWindowAspectRatio(window, 16, 9);
	glfwSetWindowSizeLimits(window, 320, 180, 1280, 720);//256 x 144 et 1920 x 1080
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << std::endl;
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
	{
		if (win->is_fullscreen == false)
		{
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1280, 720, GLFW_DONT_CARE);
			win->is_fullscreen = true;
		}
		else
		{
			glfwSetWindowMonitor(window, NULL, 0, 30, 854, 480, GLFW_DONT_CARE);
			win->is_fullscreen = false;
		}
	}
}

void Window::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->getInputManager()->setMouseButton(button, action != GLFW_RELEASE);
}

void Window::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->getInputManager()->setScroll(xoffset, yoffset);
}



void Window::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->getInputManager()->setMousePosX(xpos);
	win->getInputManager()->setMousePosY(ypos);
}

