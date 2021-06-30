#include "window.h"

Window::Window(int height, int weight, const char* windowName)
	: height(height), weight(weight), windowName(windowName)
{
}

int Window::init()
{

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(height, weight, windowName, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	return 0;
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::terminate()
{
	glfwTerminate();
}