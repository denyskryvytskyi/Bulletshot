#include "bspch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h""

#include <glad/glad.h>

#include "Game/TestsManager.h"


ImGuiLayer::ImGuiLayer()
    : m_WindowSize(0.0f), m_LastFrameFPS(0.0f), m_VSync(false), m_MTStressTest(false), m_Bullets(0), m_Walls(0)
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::Init(GLFWwindow* window, const uint16_t& screenWidth, const uint16_t& screenHeight)
{
    m_WindowSize = gdm::vec2((float)screenWidth, (float)screenHeight);

    // setup Dear ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Update(float dt)
{
    //std::cout << "Elapsed time: " << elapsed << std::endl;
    m_LastFrameFPS = 1.0f / dt;
    std::cout << "FPS: " << m_LastFrameFPS << std::endl;
}

void ImGuiLayer::Render()
{
    // ------- Begin -------
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ------- Custom panels -------
    ImGui::Begin("Statistics and Tests");
    ImGui::Text("FPS: %i", (int) m_LastFrameFPS);

    if (ImGui::Checkbox("V-Sync", &m_VSync))
    {
        glfwSwapInterval(m_VSync);
    }

    ImGui::Separator();

    if (ImGui::Checkbox("MT Stability Test", &m_MTStressTest))
    {
        TestsManager::ToggleMTStressTest();
    }

    ImGui::Columns(2);
    ImGui::Text("Bullets count: ");
    ImGui::Spacing();
    ImGui::Text("Walls count: ");

    ImGui::NextColumn();
    ImGui::PushItemWidth(200);
    ImGui::SliderInt("##walls", &m_Walls, 1, 5000);
    ImGui::SliderInt("##bullets", &m_Bullets, 1, 5000);
    ImGui::PopItemWidth();
    ImGui::Columns();

    ImGui::Spacing();

    ImGui::Indent(100.0f);
    if (ImGui::Button("Generate objects"))
    {
        TestsManager::ToggleGenerateObjects(m_Walls, m_Bullets);
    }
    ImGui::SameLine();
    if (ImGui::Button("Clean up scene"))
    {
        TestsManager::ToggleCleanupScene();
    }

    ImGui::End();

    // ------- End -------
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}