#include <iostream>
#include <GL/glew.h>

#include "window.h"
#include "shader.h"

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

    float secondTriangle[] = {
        0.0f, -0.5f,  // left
        0.9f, -0.5f,  // right
        0.45f, 0.5f  // top 
    };
  
    unsigned int indices[] = {  
        0, 1, 2
    };

    Shader firstShader("res/shaders/firstTriangleVertex.glsl", "res/shaders/firstTriangleFragment.glsl");
    Shader secondShader("res/shaders/firstTriangleVertex.glsl", "res/shaders/secondTriangleFragment.glsl");

    unsigned int vaos[2];
    glGenVertexArrays(2, vaos);
    unsigned int vbos[2];
    glGenBuffers(2, vbos);
    unsigned int ebo;
    glGenBuffers(1, &ebo);

    glBindVertexArray(vaos[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(vaos[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        firstShader.use();
        float offset = -0.1f;
        firstShader.setFloat("xOffset", offset);
        glBindVertexArray(vaos[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        secondShader.use();
        glBindVertexArray(vaos[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffers();
        window.pollEvents();
    }

    glDeleteVertexArrays(2, vaos);
    glDeleteBuffers(2, vbos);
    glDeleteBuffers(1, &ebo);

    window.terminate();

    return 0;
}