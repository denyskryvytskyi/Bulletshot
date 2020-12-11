#pragma once

#include <GLFW/glfw3.h>
#include <gdm/gdm.h>

class ImGuiLayer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void Init(GLFWwindow* window, const uint16_t& screenWidth, const uint16_t& screenHeight);
    void Shutdown();
    void Update(float dt);
    void Render();

private:
    gdm::vec2 m_WindowSize;
    float m_LastFrameFPS;
    int32_t m_Bullets;
    int32_t m_Walls;
    bool m_VSync;
    bool m_MTStressTest;
};
