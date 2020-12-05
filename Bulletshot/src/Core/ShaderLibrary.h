#pragma once

#include "Shader.h"

class ShaderLibrary
{
public:
    StrongShaderPtr Load(std::string name, const std::string& vShaderFile, const std::string& fShaderFile);

    StrongShaderPtr Get(const std::string& name);

private:
    std::string ReadFile(const std::string& shaderFile);

private:
    std::unordered_map<std::string, StrongShaderPtr> m_Shaders;
};

