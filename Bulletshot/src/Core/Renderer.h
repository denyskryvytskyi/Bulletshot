#pragma once

#include <gdm/gdm.h>
#include "Shader.h"

class Renderer
{
public:
    Renderer() = default;
    ~Renderer();

    void Init(StrongShaderPtr& shader);

    void DrawQuad(gdm::vec2 position, gdm::vec2 size, float rotateAngle, gdm::vec3 color);
    void DrawCircle(gdm::vec2 position, gdm::vec2 radius, gdm::vec3 color);

private:
    void initRenderData();

private:
    StrongShaderPtr m_Shader;
    uint32_t m_QuadVAO;
    uint32_t m_CircleVAO;
};

