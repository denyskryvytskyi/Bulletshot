#include "bspch.h"
#include "Game.h"
#include "TestsManager.h"

const uint32_t maxThreadsCount = 4;

Game::~Game()
{
    Cleanup();
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

    m_SceneManager.Init((float)screenWidth, (float)screenHeight);

    // Init bullets and walls
    // With threads 
   /* for (size_t i = 0; i < maxThreadsCount; i++)
    {
        m_Threads.emplace_back(std::thread(&Game::PerformanceStressTest, this, 250));
    }*/
    // Without threads
    PerformanceStressTest(1);
    GenerateWalls(1);
    //
}

void Game::ProcessInput(float dt)
{
    // ÑÄÅËÀÒÜ ÑÒÐÅËÜÁÓ ÏÎ ÍÀÆÀÒÈÞ
}

void Game::Update(float dt)
{
    // MT Stress Test
    if (TestsManager::m_AllowMTStabilityStressTest)
    {
        for (uint32_t i = 0; i < maxThreadsCount; i++)
        {
            m_Threads.emplace_back(std::thread(&Game::MTStabilityStressTest, this, 6));
        }
    }

    if (TestsManager::m_GenerateObjects)
    {
        m_SceneManager.CreateScene(TestsManager::m_WallsCount, TestsManager::m_BulletsCount);
        TestsManager::ToggleGenerateObjects();

        // generate walls and bullets by created scene infos
        GenerateBullets(m_SceneManager.GetBulletsInfo());
        GenerateWalls(m_SceneManager.GetWallsInfo());
    }

    if (TestsManager::m_CleanupScene)
    {
        Cleanup();
        TestsManager::ToggleCleanupScene(false);
    }

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

void Game::Cleanup()
{
    for (uint32_t i = 0; i < m_Threads.size(); i++)
    {
        std::thread& thread = m_Threads[i];
        if (thread.joinable())
        {
            thread.join();
        }
    }
    m_Threads.clear();

    g_Physics.Cleanup();
    m_BulletManager.Cleanup();
    m_WallManager.Cleanup();
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
    for (uint32_t j = 0; j < bulletsCount; j++)
    {
        gdm::vec2 pos(10.0f, 100.0f + j * 20.0f);
        gdm::vec2 dir(1.0f, 0.0f);
        float speed = 100.0f;
        float timeToSpawn = 3.0f;
        float lifetime = 10.0f;

        m_BulletManager.Fire(pos, dir, speed, timeToSpawn, lifetime);
    }
}

// Perfomance Stress Test
void Game::PerformanceStressTest(int32_t bulletsCount)
{
    for (uint32_t j = 0; j < bulletsCount; j++)
    {
        gdm::vec2 pos(10.0f + j * 40.0f, 10.0f);
        //gdm::vec2 pos(10.0f, 100.0f);
        gdm::vec2 dir(0.5f, 0.555f);
        float speed = 300.0f;
        float timeToSpawn = 3.0f;
        float lifetime = 10.0f;

        m_BulletManager.Fire(pos, dir, speed, timeToSpawn, lifetime);
    }
}

// ----------------------------------------------------------

void Game::GenerateBullets(const std::vector<BulletStartupInfo> bulletsInfo)
{
    uint32_t bulletsPerThreadCount = (uint32_t) bulletsInfo.size() / maxThreadsCount;

    for (uint32_t i = 0; i < maxThreadsCount; ++i)
    {
        uint32_t startIndex = i * bulletsPerThreadCount;
        std::vector<BulletStartupInfo> threadBullets(bulletsInfo.begin() + startIndex, bulletsInfo.begin() + startIndex + bulletsPerThreadCount);
        m_Threads.emplace_back(std::thread(&Game::GenerateBulletsInThread, this, threadBullets));
    }
}

void Game::GenerateBulletsInThread(const std::vector<BulletStartupInfo> bulletsInfo)
{
    for (const BulletStartupInfo& info : bulletsInfo)
    {
        m_BulletManager.Fire(info.Position, info.Direction, info.Speed, info.TimeToSpawn, info.LifeTime);
    }
}

void Game::GenerateWalls(const std::vector<WallStartupInfo>& wallsInfo)
{
    for (const WallStartupInfo& info : wallsInfo)
    {
        m_WallManager.CreateWall(info.Position, info.Size, info.Rotation);
    }
}

void Game::GenerateWalls(int32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        gdm::vec2 pos(100.0f + i * 60.0f, 500.0f);
        //gdm::vec2 pos(10.0f, 600.0f);
        gdm::vec2 size(500.0f, 10.0f);
        float rotation = 91.0f; /// Ïîñìîòðåòü ïî÷åìó ñäâèãàåòñÿ ïðè òàêèõ íå÷åòíûõ ÷èñëàõ

        m_WallManager.CreateWall(pos, size, rotation);
    }
}