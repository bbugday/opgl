#include <iostream>
#include <GL/glew.h>

#include "window.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

float offsetX = 0;
float offsetY = 0;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float speed = 0.05f;

    if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_LEFT)
        {
            offsetX -= speed;
        }
        if (key == GLFW_KEY_RIGHT)
        {
            offsetX += speed;
        }
        if (key == GLFW_KEY_UP)
        {
            offsetY += speed;
        }
        if (key == GLFW_KEY_DOWN)
        {
            offsetY -= speed;
        }
    }
}

int main(void)
{
    Window window(800, 800, "Hello World");

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

    const float length = 0.05f;
    const float halfLength = length / 2;

    float squareVertex[] = {
         halfLength,  halfLength,
        -halfLength,  halfLength,
        -halfLength, -halfLength,
         halfLength, -halfLength
    };

    unsigned int squareIndices[] = {
        0, 1, 3,
        1, 2, 3
    };

    Shader squareShader("res/shaders/squareVertex.glsl", "res/shaders/squareFragment.glsl");

    Vao squareVao;
    Vbo squareVbo(squareVertex, sizeof(squareVertex));
    squareVbo.attribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    Ebo squareEbo(squareIndices, sizeof(squareIndices));

    squareVao.unbind();
    squareVbo.unbind();
    squareEbo.unbind();

    unsigned int squareCount = 5;

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        squareVao.bind();

        squareShader.use();

        for (int i = 0; i < squareCount; i++)
        {
            squareShader.setVec2Float("offset", offsetX - length * i, offsetY);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        window.swapBuffers();
        window.pollEvents();
    }

    window.terminate();

    return 0;
}


