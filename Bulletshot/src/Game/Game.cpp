#include "bspch.h"
#include "Game.h"
#include "TestsManager.h"

Game::Game()
    : m_MaxThreadsCount(4)
{
}

Game::~Game()
{
    Cleanup();
}

void Game::Init(uint16_t screenWidth, uint16_t screenHeight)
{
    // Camera
    m_Camera.SetProjection(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);

    // Shaders
    StrongShaderPtr shader = m_ShaderLibrary.Load("default_shader");
    shader->Bind();
    shader->SetMatrix4("u_Proj", m_Camera.GetProjectionMatrix());

    // Renderer
    m_Renderer.Init(shader);

    // Scene
    m_SceneManager.Init((float)screenWidth, (float)screenHeight);

    // Init predefined bullets and walls
    m_SceneManager.CreateScene();
    GenerateBullets(m_SceneManager.GetBulletsInfo());
    GenerateWalls(m_SceneManager.GetWallsInfo());
}

void Game::Update(float dt)
{
    if (TestsManager::m_AllowMTStabilityStressTest)
    {
        for (uint32_t i = 0; i < m_MaxThreadsCount; i++)
        {
            m_SceneManager.CreateScene(0, 30);

            // generate walls and bullets by created scene info
            GenerateBullets(m_SceneManager.GetBulletsInfo());
            GenerateWalls(m_SceneManager.GetWallsInfo());
        }
    }

    if (TestsManager::m_GenerateObjects)
    {
        m_SceneManager.CreateScene(TestsManager::m_WallsCount, TestsManager::m_BulletsCount);
        TestsManager::ToggleGenerateObjects();

        // generate walls and bullets by created scene info
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

void Game::GenerateBullets(const std::vector<BulletStartupInfo>& bulletsInfo)
{
    uint32_t bulletsPerThreadCount = (uint32_t) (bulletsInfo.size() / m_MaxThreadsCount);

    for (uint32_t i = 0; i < m_MaxThreadsCount; ++i)
    {
        uint32_t startIndex = i * bulletsPerThreadCount;
        std::vector<BulletStartupInfo> threadBullets(bulletsInfo.begin() + startIndex,
            i == m_MaxThreadsCount - 1 ? bulletsInfo.end() : bulletsInfo.begin() + startIndex + bulletsPerThreadCount);
        if (!threadBullets.empty())
        {
            // Pass copy of threadBullets because original is destroyed at the iteration end
            m_Threads.emplace_back(std::thread(&Game::GenerateBulletsInThread, this, threadBullets));
        }
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