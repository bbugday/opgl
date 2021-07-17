#ifdef MAIN

#include <iostream>
#include <GL/glew.h>

#include "engine/window.h"
#include "engine/shader.h"
#include "engine/vao.h"
#include "engine/vbo.h"
#include "engine/ebo.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"

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

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        tShader.use();

        glBindTexture(GL_TEXTURE_2D, texture);

        vao.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffers();
        window.pollEvents();
    }

    window.terminate();

    return 0;
}

#endif


