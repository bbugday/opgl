#include <iostream>
#include <GL/glew.h>

#include "window.h"


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



    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        window.swapBuffers();

        /* Poll for and process events */
        window.pollEvents();
    }

    window.terminate();

    return 0;
}