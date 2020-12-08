#include "bspch.h"
#include "Game.h"
#include "WallObject.h"

//extern std::mutex g_Mutex;
const unsigned int maxThreadsCount = 4;

Game::Game()
{
}

Game::~Game()
{
    for (size_t i = 0; i < m_Threads.size(); i++)
    {
        m_Threads[i].join();
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

    // With threads 
    /*for (size_t i = 0; i < maxThreadsCount; i++)
    {
        m_Threads.push_back(std::thread(&Game::PerformanceStressTest, this, 25));
    }*/
    //
    PerformanceStressTest(150);
    GenerateWalls(150);

    // Init Renderer
    m_Renderer.Init(shader);
    //
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
    // Bullets update
    m_BulletManager.Update(dt);

    // MT Stress Test
    /*for (size_t i = 0; i < maxThreadsCount; i++)
    {
        m_Threads.push_back(std::thread(&Game::MTStabilityStressTest, this, 6));
    }*/

    // Walls update
    for (auto wallIterator = m_Walls.begin(); wallIterator != m_Walls.end();)
    {
        if ((*wallIterator)->IsDestroyed())
        {
            Game::OnGameobjectDestroyed(*wallIterator);
            delete *wallIterator;
            wallIterator = m_Walls.erase(wallIterator);
        }
        else
        {
            ++wallIterator;
        }
    }

    // Physics update
    g_Physics.DoCollisions();
}


void Game::Render()
{
    for (auto wall : m_Walls)
    {
        wall->Draw(m_Renderer);
    }

    for (auto bullet : m_BulletManager.GetBulletObjects())
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
        gdm::vec2 pos(10.0f + j * 40.0f, 10.0f);
        //gdm::vec2 pos(10.0f, 100.0f);
        gdm::vec2 dir(1.0f, 0.99999f);
        float speed = 200.0f;
        float timeToSpawn = 3.0f;
        float lifetime = 5.0f;

        m_BulletManager.Fire(pos, dir, speed, timeToSpawn, lifetime);
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

void Game::GenerateWalls(int32_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        gdm::vec2 pos(10.0f + i * 50.0f, 600.0f);
        //gdm::vec2 pos(10.0f, 600.0f);
        gdm::vec2 size(500.0f, 20.0f);
        float rotation = 0.0f;

        WallObject* wall = new WallObject(pos, size, rotation);
        m_Walls.push_back(wall);

        //OnGameobjectSpawned(wall);
        g_Physics.RegisterObject(wall);
    }
}