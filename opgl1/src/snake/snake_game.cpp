#ifdef SNAKE_GAME

#include <iostream>
#include <GL/glew.h>

#include "../engine/window.h"
#include "../engine/error_check.h"
#include "snake.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Snake* snake;

int main(void)
{
    Window window(800, 800, "opgl");

    if (window.init())
    {
        std::cout << "GLFW failed";
        return -1;
    }

    window.setKeyCallback(keyCallback);

    GLenum err = glewInit();

    if (GLEW_OK != err)
    {
        std::cout << "Error: " << glewGetErrorString(err);
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    snake = new Snake;

    const double maxFPS = 60.0;
    const double maxPeriod = 1.0 / maxFPS;

    double lastTime = 0.0;

    while (!window.shouldClose())
    {
        double time = glfwGetTime();
        double deltaTime = time - lastTime;

        if (deltaTime >= maxPeriod)
        {
            lastTime = time;
            GLCALL(glClear(GL_COLOR_BUFFER_BIT));

            snake->draw();
            snake->update();


            window.swapBuffers();
            window.pollEvents();
        }
    }

    window.terminate();

    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_LEFT)
        {
            snake->input(Direction::LEFT);
        }
        if (key == GLFW_KEY_RIGHT)
        {
            snake->input(Direction::RIGHT);
        }
        if (key == GLFW_KEY_UP)
        {
            snake->input(Direction::UP);
        }
        if (key == GLFW_KEY_DOWN)
        {
            snake->input(Direction::DOWN);
        }
        if (key == GLFW_KEY_SPACE)
        {
            snake->addSquare();
        }
    }
}

#endif


