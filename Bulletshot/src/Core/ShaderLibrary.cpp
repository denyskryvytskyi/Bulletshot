#include "bspch.h"
#include "ShaderLibrary.h"

const char vertexShaderSrc[] = R"(
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_Proj;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Proj * u_Model * position;
}
)";

const char fragmentShaderSrc[] = R"(
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_Color;

void main()
{
    color = vec4(u_Color, 1.0);
}
)";

StrongShaderPtr ShaderLibrary::Load(std::string name, const std::string& vShaderFile, const std::string& fShaderFile)
{
    ShaderProgramSource shaderProgram;

    /*shaderProgram.VertexSource = ReadFile(vShaderFile);
    shaderProgram.FragmentSource = ReadFile(fShaderFile);*/
    
    shaderProgram.VertexSource = vertexShaderSrc;
    shaderProgram.FragmentSource = fragmentShaderSrc;

    StrongShaderPtr shader = std::make_shared<Shader>(name, shaderProgram);
    m_Shaders[name] = shader;

    return shader;
}

StrongShaderPtr ShaderLibrary::Get(const std::string& name)
{
    return m_Shaders[name];
}

std::string ShaderLibrary::ReadFile(const std::string& shaderFile)
{
    std::string result;
    std::ifstream in(shaderFile, std::ios::in || std::ios::binary);
    if (in)
    {
        in.seekg(0, in.end);
        result.resize(in.tellg());
        in.seekg(0, in.beg);
        in.read(&result[0], result.size());
        in.close();
    }
    else
    {
        ASSERT(false);
    }

    return result;
}
