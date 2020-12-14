#include "bspch.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Core/TimeStamp.h"
#include "Core/ImGui/ImGuiLayer.h"
#include "Game/Game.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int WinMain(struct HINSTANCE__* hInstance, struct HINSTANCE__* hPrevInstance, char* lpszCmdLine, int nCmdShow)
{
    if (!glfwInit())
    {
        ASSERT(false);
    }

    // Create window
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

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ASSERT(false);
        return -1;
    }

    // Set callbacks
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
        float elapsed = timestamp.Elapsed();
        timestamp.Restart();

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
