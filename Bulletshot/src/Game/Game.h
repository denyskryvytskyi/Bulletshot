#pragma once

#include "Core/Renderer.h"
#include "Core/ShaderLibrary.h"
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

private:
    Renderer m_Renderer;
    ShaderLibrary m_ShaderLibrary;
    BulletManager m_BulletManager;

    // temp
    std::vector<std::thread> threads;
};

