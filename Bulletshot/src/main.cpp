#include "bspch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Game.h"
#include "ShaderLibrary.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // glfw init
    if (!glfwInit())
    {
        ASSERT(false);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    const uint32_t screenWidth = 1280;
    const uint32_t screenHeight = 720;

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

    // Game init
    Game game;
    game.Init();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //std::cout << "Main loop" << std::endl;
        game.ProcessInput(0);

        game.Update(0);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        glfwSwapBuffers(window);
    }

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
