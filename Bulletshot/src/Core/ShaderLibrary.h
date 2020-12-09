#pragma once

#include "Shader.h"

class ShaderLibrary
{
public:
    StrongShaderPtr Load(std::string name);
    StrongShaderPtr Get(const std::string& name);

private:
    std::unordered_map<std::string, StrongShaderPtr> m_Shaders;
};

