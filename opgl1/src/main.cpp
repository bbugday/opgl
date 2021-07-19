#ifdef MAIN

#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"


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

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, 
        1, 2, 3
    };

    Shader tShader("res/shaders/tVertex.glsl", "res/shaders/tFragment.glsl");

    Vao vao;
    Vbo vbo(vertices, sizeof(vertices));
    vbo.attribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    vbo.attribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vbo.attribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    Ebo ebo(indices, sizeof(indices));

    Texture t1("res/textures/container.jpg", GL_REPEAT, GL_RGB);
    Texture t2("res/textures/awesomeface.png", GL_REPEAT, GL_RGBA);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();
    t2.unbind();

    tShader.use();
    tShader.setInt("texture1", 0);
    tShader.setInt("texture2", 1);

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = glm::mat4(1.0f);

        trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        tShader.use();
        tShader.setMatrix4fv("transform", 1, GL_FALSE, glm::value_ptr(trans));

        t1.activeAndBind(0);
        t2.activeAndBind(1);

        vao.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));
        float scaleAmount = sin(glfwGetTime());
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        tShader.setMatrix4fv("transform", 1, GL_FALSE,& trans[0][0]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffers();
        window.pollEvents();
    }

    window.terminate();

    return 0;
}

#endif


