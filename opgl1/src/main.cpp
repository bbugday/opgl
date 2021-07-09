#include <iostream>
#include <GL/glew.h>

#include "window.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

int main(void)
{
    Window window(800, 800, "Hello World");

    if (window.init())
    {
        std::cout << "GLFW failed";
        return -1;
    }

    GLenum err = glewInit();

    if (GLEW_OK != err)
    {
        std::cout << "Error: " << glewGetErrorString(err);
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    float squareVertex[] = {
         0.025f,  0.025f,
        -0.025f,  0.025f,
        -0.025f, -0.025f,
         0.025f, -0.025f
    };

    unsigned int squareIndices[] = {
        0, 1, 3,
        1, 2, 3
    };

    float offset = 0.1f;

    Shader squareShader("res/shaders/squareVertex.glsl", "res/shaders/squareFragment.glsl");

    Vao squareVao;
    Vbo squareVbo(squareVertex, sizeof(squareVertex));
    squareVbo.attribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    Ebo squareEbo(squareIndices, sizeof(squareIndices));

    squareVao.unbind();
    squareVbo.unbind();
    squareEbo.unbind();

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        squareShader.use();
        squareVao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffers();
        window.pollEvents();
    }

    window.terminate();

    return 0;
}