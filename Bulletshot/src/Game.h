#pragma once

#include "Renderer.h"
#include "ShaderLibrary.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

private:
    Renderer m_Renderer;
    ShaderLibrary m_ShaderLibrary;
};

