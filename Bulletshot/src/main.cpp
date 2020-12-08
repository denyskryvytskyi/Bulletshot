#include "bspch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Game/Game.h"
#include "Core/Timer.h"

//
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//

int main()
{
    // glfw init
    if (!glfwInit())
    {
        ASSERT(false);
    }

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
    //glfwSwapInterval(1); // vsync

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

    Timer timer;
    while (!glfwWindowShouldClose(window))
    {
        float elapsed = timer.elapsed();
        timer.restart();

        std::cout << "Elapsed time: " << elapsed << std::endl;
        std::cout << "FPS: " << 1.0f / elapsed << std::endl;

        glfwPollEvents();

        game.ProcessInput(elapsed);

        game.Update(elapsed);

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
