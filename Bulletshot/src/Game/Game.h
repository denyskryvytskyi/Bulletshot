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
    Game();
    ~Game();

    void Init(uint16_t screenWidth, uint16_t screenHeight);
    void Update(float dt);
    void Render();
    void Cleanup();

    static void OnGameobjectSpawned(GameObject* gameobject);
    static void OnGameobjectDestroyed(GameObject* gameobject);

private:
    void GenerateBullets(const std::vector<BulletStartupInfo>& bulletsInfo);
    // Pass copy of info vector
    void GenerateBulletsInThread(const std::vector<BulletStartupInfo> bulletsInfo);

    void GenerateWalls(const std::vector<WallStartupInfo>& wallsInfo);

private:
    Renderer m_Renderer;
    Camera m_Camera;
    ShaderLibrary m_ShaderLibrary;
    BulletManager m_BulletManager;
    WallManager m_WallManager;
    SceneManager m_SceneManager;

    std::vector<std::thread> m_Threads;
    const uint32_t m_MaxThreadsCount;
};