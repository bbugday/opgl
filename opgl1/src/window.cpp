#include "window.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwTerminate();
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_LEFT)
		{
			
		}
		if (key == GLFW_KEY_RIGHT)
		{

		}
		if (key == GLFW_KEY_UP)
		{

		}
		if (key == GLFW_KEY_DOWN)
		{

		}
	}
}

Window::Window(int height, int weight, const char* windowName)
	: height(height), weight(weight), windowName(windowName), window(nullptr)
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

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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