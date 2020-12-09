#include "bspch.h"
#include "Game.h"

const unsigned int maxThreadsCount = 4;

Game::~Game()
{
    for (size_t i = 0; i < m_Threads.size(); i++)
    {
        m_Threads[i].join();
    }
}

void Game::Init(const uint16_t& screenWidth, const uint16_t& screenHeight)
{
    // Init Camera
    m_Camera.SetProjection(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);

    // Shaders
    StrongShaderPtr shader = m_ShaderLibrary.Load("default_shader");
    shader->Bind();
    shader->SetMatrix4("u_Proj", m_Camera.GetProjectionMatrix());
    //

    // Init Renderer
    m_Renderer.Init(shader);
    //

    // Init bullets and walls
    // With threads 
    for (size_t i = 0; i < maxThreadsCount; i++)
    {
        m_Threads.push_back(std::thread(&Game::PerformanceStressTest, this, 40));
    }
    // Without threads
    //PerformanceStressTest(160);
    GenerateWalls(150);
    //
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
    // MT Stress Test
    /*for (size_t i = 0; i < maxThreadsCount; i++)
    {
        m_Threads.push_back(std::thread(&Game::MTStabilityStressTest, this, 6));
    }*/

    // Bullets update
    m_BulletManager.Update(dt);

    // Walls update
    m_WallManager.Update();

    // Physics update
    g_Physics.DoCollisions(dt);
}


void Game::Render()
{
    for (auto wall : m_WallManager.GetWalls())
    {
        wall->Draw(m_Renderer);
    }

    for (auto bullet : m_BulletManager.GetBulletObjects())
    {
        bullet->Draw(m_Renderer);
    }
}

void Game::OnGameobjectSpawned(GameObject* gameobject)
{
    g_Physics.RegisterObject(gameobject);
}

void Game::OnGameobjectDestroyed(GameObject* gameobject)
{
    g_Physics.UnregisterObject(gameobject);
}

// ----------------------------------------------------------

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
        gdm::vec2 pos(10.0f + j * 40.0f, 10.0f);
        //gdm::vec2 pos(10.0f, 100.0f);
        gdm::vec2 dir(0.0f, 0.5f);
        float speed = 300.0f;
        float timeToSpawn = 3.0f;
        float lifetime = 5.0f;

        m_BulletManager.Fire(pos, dir, speed, timeToSpawn, lifetime);
    }
}

void Game::GenerateWalls(int32_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        gdm::vec2 pos(10.0f + i * 60.0f, 500.0f);
        //gdm::vec2 pos(10.0f, 600.0f);
        gdm::vec2 size(50.0f, 10.0f);
        float rotation = 0.0f;

        m_WallManager.CreateWall(pos, size, rotation);
    }
}