#include "bspch.h"
#include "Game.h"

extern std::mutex g_Mutex;
const unsigned int maxThreadsCount = 4;

Game::Game()
{
}

Game::~Game()
{
    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
}

void Game::Init()
{
    // Init Camera
    StrongShaderPtr shader = m_ShaderLibrary.Load("default_shader", "res/shaders/vertex.vs", "res/shaders/fragment.fs");
    gdm::mat4 proj = gdm::orthographic(0.0f, (float)1280, 0.0f, (float)720, -1.0f, 1.0f);
    shader->Bind();
    shader->SetMatrix4("u_Proj", proj);
    //

    // Perfomance stress test
    // Without threads
    //PerformanceStressTest(2000);

    // With threads 
    for (size_t i = 0; i < maxThreadsCount; i++)
    {
        threads.push_back(std::thread(&Game::PerformanceStressTest, this, 125));
    }
    //

    // Init Renderer
    m_Renderer.Init(shader);
    //
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
    // Physics update

    // Bullets update
    m_BulletManager.Update(dt);

    // MT Stress Test
    /*for (size_t i = 0; i < maxThreadsCount; i++)
    {
        threads.push_back(std::thread(&Game::MTStabilityStressTest_1, this, 6));
    }*/

    // Walls update
}


void Game::Render()
{
    // draw all gameobjects
    // foreach(m_Gameobjects) -> draw

    for (size_t i = 0; i < 500; i++)
    {
        m_Renderer.DrawQuad({ 10.0f + i, 10.0f}, { 70.0f, 200.0f }, 0.0f, { 0.0f, 1.0f, 1.0f });
    }

    // wrap this into lock_guard
    std::lock_guard<std::mutex> lock(g_Mutex);
    for (StrongBulletPtr bullet : m_BulletManager.GetBulletObjects())
    {
        bullet->Draw(m_Renderer);
    }
}

// MT Stress Test
void Game::MTStabilityStressTest(int32_t bulletsCount)
{
    for (size_t j = 0; j < bulletsCount; j++)
    {
        gdm::vec2 pos(10.0f, 100.0f + j * 20.0f);
        gdm::vec2 dir(1.0f, 0.0f);
        float speed = 100.0f;
        float timeToSpawn = 3.0f;
        float lifetime = 5.0f;

        m_BulletManager.Fire(pos, dir, speed, timeToSpawn, lifetime);
    }
}

// Perfomance Stress Test
void Game::PerformanceStressTest(int32_t bulletsCount)
{
    for (size_t j = 0; j < bulletsCount; j++)
    {
        gdm::vec2 pos(10.0f, 100.0f);
        gdm::vec2 dir(1.0f, 0.0f);
        float speed = 100.0f;
        float timeToSpawn = 3.0f;
        float lifetime = 5.0f;

        m_BulletManager.Fire(pos, dir, speed, timeToSpawn, lifetime);
    }
}
