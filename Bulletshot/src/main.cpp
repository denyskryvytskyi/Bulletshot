#include "bspch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // glfw init
    if (!glfwInit())
    {
        ASSERT(false);
    }

    // create window
    const unsigned int screenWidth = 1280;
    const unsigned int screenHeight = 720;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Bulletshot", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        ASSERT(false);
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // load opengl functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ASSERT(false);
        return -1;
    }

#ifdef DEBUG
    std::cout << "OpenGL info:\n Vendor: " << glGetString(GL_VENDOR) << "\n Renderer: " << glGetString(GL_RENDERER) << "\n Version: " << glGetString(GL_VERSION) << std::endl;
#endif

    // set callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        std::cout << "Main loop" << std::endl;
    }

    system("pause");
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
