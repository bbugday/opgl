#ifdef MAIN

#include <iostream>
#include <GL/glew.h>

#include "engine/window.h"
#include "engine/shader.h"
#include "engine/vao.h"
#include "engine/vbo.h"
#include "engine/ebo.h"

int main(void)
{
    Window window(640, 480, "Hello World");

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

    float firstTriangle[] = {

        //positions    //colors
        -0.9f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.0f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.45f, 0.5f,  0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    Shader firstShader("res/shaders/firstTriangleVertex.glsl", "res/shaders/firstTriangleFragment.glsl");

    Vao vao;
    Vbo vbo(firstTriangle, sizeof(firstTriangle));
    vbo.attribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    vbo.attribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    Ebo ebo(indices, sizeof(indices));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        float offset = -0.1f;
        firstShader.setFloat("xOffset", offset);

        firstShader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffers();
        window.pollEvents();
    }

    window.terminate();

    return 0;
}

#endif


