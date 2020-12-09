#include "bspch.h"
#include "ShaderLibrary.h"

StrongShaderPtr ShaderLibrary::Load(std::string name)
{
    ShaderProgramSource shaderProgram;

    shaderProgram.VertexSource = R"(
        #version 330 core

        layout(location = 0) in vec4 position;

        uniform mat4 u_Proj;
        uniform mat4 u_Model;

        void main()
        {
            gl_Position = u_Proj * u_Model * position;
        }
        )";
    shaderProgram.FragmentSource = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        uniform vec3 u_Color;

        void main()
        {
            color = vec4(u_Color, 1.0);
        }
        )";

    StrongShaderPtr shader = std::make_shared<Shader>(name, shaderProgram);
    m_Shaders[name] = shader;

    return shader;
}

StrongShaderPtr ShaderLibrary::Get(const std::string& name)
{
    return m_Shaders[name];
}