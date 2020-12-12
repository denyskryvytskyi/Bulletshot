#include "bspch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Core/TimeStamp.h"
#include "Core/ImGui/ImGuiLayer.h"
#include "Game/Game.h"

//
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//

int WinMain()
{
    // glfw init
    if (!glfwInit())
    {
        ASSERT(false);
    }

    // create window
    const uint16_t screenWidth = 1280;
    const uint16_t screenHeight = 720;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Bulletshot", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        ASSERT(false);
        return -1;
    }
    glfwMakeContextCurrent(window);

    // load opengl functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ASSERT(false);
        return -1;
    }

    // set callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ImGui init
    ImGuiLayer ImGuiLayer;
    ImGuiLayer.Init(window, screenWidth, screenHeight);

    // Game init
    Game game;
    game.Init(screenWidth, screenHeight);

    TimeStamp timestamp;
    while (!glfwWindowShouldClose(window))
    {
        float elapsed = timestamp.elapsed();
        timestamp.restart();

        glfwPollEvents();

        ImGuiLayer.Update(elapsed);

        game.Update(elapsed);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        ImGuiLayer.Render();

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
