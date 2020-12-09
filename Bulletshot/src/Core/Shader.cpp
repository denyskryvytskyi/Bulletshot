#include "bspch.h"
#include "Shader.h"
#include <glad/glad.h>

Shader::Shader()
    : m_RendererId(0)
{
}

Shader::Shader(const std::string& name, const ShaderProgramSource& shaderSource)
    : m_Name(name), m_RendererId(0)
{
    CompileProgram(shaderSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererId);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetVector3f(const std::string& name, const gdm::vec3& vector)
{
    glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::SetMatrix4(const std::string& name, const gdm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.ElementsPtr());
}

void Shader::CompileProgram(const ShaderProgramSource& shaderSource)
{
    m_RendererId = glCreateProgram();
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, shaderSource.VertexSource);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, shaderSource.FragmentSource);

    glAttachShader(m_RendererId, vs);
    glAttachShader(m_RendererId, fs);
    glLinkProgram(m_RendererId);

    int32_t isLinked = 0;
    glGetProgramiv(m_RendererId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        int32_t maxLength = 0;
        glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

        // todo: remove
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);

        std::cout << "Failed program linking: " << infoLog.data() << std::endl;
        //
        glDeleteProgram(m_RendererId);

        ASSERT(false);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
    uint32_t shaderId = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    int32_t isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        int32_t maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        /*
        * Либо добавить вывод в лог, либо удалить вообще
        */
        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

        std::cout << "Failed shader compile: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment", " shader:") << infoLog.data() << std::endl;
        //

        glDeleteShader(shaderId);

        ASSERT(false);

        return -1;
    }

    return shaderId;
}

int32_t Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int32_t location = glGetUniformLocation(m_RendererId, name.c_str());
    m_UniformLocationCache[name] = location;

    return location;
}
