#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int height, int weight, const char* windowName);
	int init();
	bool shouldClose();
	void swapBuffers();
	void pollEvents();
	void terminate();
	void setKeyCallback(GLFWkeyfun callback);
private:
	GLFWwindow* window;
	int height;
	int weight;
	const char* windowName;
};