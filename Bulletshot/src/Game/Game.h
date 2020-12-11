#pragma once

#include "Core/Renderer.h"
#include "Core/Camera.h"
#include "Core/ShaderLibrary.h"
#include "SceneManager.h"
#include "BulletManager.h"
#include "WallManager.h"

class Game
{
public:
    Game() = default;
    ~Game();

    void Init(const uint16_t& screenWidth, const uint16_t& screenHeight);
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void Cleanup();

    static void OnGameobjectSpawned(GameObject* gameobject);
    static void OnGameobjectDestroyed(GameObject* gameobject);

    // tests
    void MTStabilityStressTest(int32_t bulletsCount);
    void PerformanceStressTest(int32_t bulletsCount);

private:
    void GenerateWalls(int32_t count);

private:
    Renderer m_Renderer;
    Camera m_Camera;
    ShaderLibrary m_ShaderLibrary;
    BulletManager m_BulletManager;
    WallManager m_WallManager;
    SceneManager m_SceneManager;

    std::vector<std::thread> m_Threads;
};