#pragma once

#include <gdm/gdm.h>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:
    Shader();
    Shader(const std::string& name, const ShaderProgramSource& shaderSource);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetVector3f(const std::string& name, const gdm::vec3& vector);
    void SetMatrix4(const std::string& name, const gdm::mat4& matrix);

    void CompileProgram(const ShaderProgramSource& shaderSource);

private:
    int32_t CompileShader(uint32_t type, const std::string& source);
    int32_t GetUniformLocation(const std::string& name);

private:
    std::unordered_map<std::string, int32_t> m_UniformLocationCache;
    std::string m_Name;
    uint32_t m_RendererId;
};

typedef std::shared_ptr<Shader> StrongShaderPtr;