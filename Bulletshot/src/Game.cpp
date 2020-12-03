#include "bspch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    // Camera
    StrongShaderPtr shader = m_ShaderLibrary.Load("default_shader", "res/shaders/vertex.vs", "res/shaders/fragment.fs");
    gdm::mat4 proj = gdm::orthographic(0.0f, (float)1280, 0.0f, (float)720, -1.0f, 1.0f);
    shader->Bind();
    shader->SetMatrix4("u_Proj", proj);
    //

    m_Renderer.Init(shader);
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}


void Game::Render()
{
    m_Renderer.DrawQuad({ 1000.0f, 300.0f }, { 70.0f, 200.0f }, 120.0f, { 0.0f, 1.0f, 1.0f });
    m_Renderer.DrawCircle({ 300.0f, 100.0f }, 15.0f, { 1.0f, 1.0f, 0.0f });
}
