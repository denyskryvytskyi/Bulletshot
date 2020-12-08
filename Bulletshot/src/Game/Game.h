#pragma once

#include "Core/Renderer.h"
#include "Core/ShaderLibrary.h"
#include "Core/Physics.h"

#include "BulletManager.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    // tests
    void MTStabilityStressTest(int32_t bulletsCount);
    void PerformanceStressTest(int32_t bulletsCount);

    //
    static void OnGameobjectSpawned(GameObject* gameobject);
    static void OnGameobjectDestroyed(GameObject* gameobject);

private:
    void GenerateWalls(int32_t count);

private:
    Renderer m_Renderer;
    ShaderLibrary m_ShaderLibrary;
    BulletManager m_BulletManager;
    //Physics m_Physics;

    std::vector<std::thread> m_Threads;

    std::vector<GameObject*> m_Walls;
};

