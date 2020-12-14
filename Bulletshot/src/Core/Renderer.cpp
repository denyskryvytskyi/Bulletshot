#include "bspch.h"
#include "Renderer.h"
#include <glad/glad.h>

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &m_QuadVAO);
    glDeleteVertexArrays(1, &m_CircleVAO);
}

void Renderer::Init(StrongShaderPtr& shader)
{
    m_Shader = shader;
    initRenderData();
}

void Renderer::DrawQuad(gdm::vec2 position, gdm::vec2 size, float rotateAngle, gdm::vec3 color)
{
    m_Shader->Bind();
    // Model matrix : scale->rotation->translation
    gdm::mat4 model =
        // Scale
        gdm::scale(gdm::mat4(), gdm::vec3(size.x, size.y, 1.0f))
        // Rotation around center
        * gdm::translate(gdm::mat4(), gdm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f))
        * gdm::rotate(gdm::mat4(), rotateAngle, gdm::vec3(0.0f, 0.0f, 1.0f))
        * gdm::translate(gdm::mat4(), gdm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f))
        // Translation
        * gdm::translate(gdm::mat4(), gdm::vec3(position.x, position.y, 0.0f));

    m_Shader->SetMatrix4("u_Model", model);
    m_Shader->SetVector3f("u_Color", color);

    glBindVertexArray(m_QuadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawCircle(gdm::vec2 position, gdm::vec2 radius, gdm::vec3 color)
{
    m_Shader->Bind();
    // Model matrix : scale->rotation->translation
    gdm::mat4 model =
        // Scale
        gdm::scale(gdm::mat4(), gdm::vec3(radius.x, radius.y, 1.0f))
        // Translation
        * gdm::translate(gdm::mat4(), gdm::vec3(position.x, position.y, 0.0f));

    m_Shader->SetMatrix4("u_Model", model);
    m_Shader->SetVector3f("u_Color", color);

    glBindVertexArray(m_CircleVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
}

void Renderer::initRenderData()
{
    // ----------- QUAD -----------
    uint32_t quadVBO;
    float quadVertices[] = {
       0.0f, 1.0f,
       1.0f, 0.0f,
       0.0f, 0.0f, // left down - position of quad
       1.0f, 1.0f
    };

    glGenVertexArrays(1, &m_QuadVAO);
    glGenBuffers(1, &quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    uint32_t quadIBO;
    unsigned int quadIndecies[] = {
        0, 1, 2,
        0, 3, 1
    };
    glGenBuffers(1, &quadIBO);

    glBindVertexArray(m_QuadVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndecies), quadIndecies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // ----------- CIRCLE -----------
    const int32_t segmentsCount = 40;
    float circleVertices[segmentsCount];
    float pi = (float)gdm::PI;
    for (uint16_t i = 0; i < segmentsCount; i += 2)
    {
        float theta = 2.0f * pi * float(i) / float(segmentsCount); // get the current angle

        circleVertices[i] = cosf(theta); // calculate the x component
        circleVertices[i + 1] = sinf(theta); // calculate the y component
    }

    uint32_t circleVBO;
    glGenVertexArrays(1, &m_CircleVAO);
    glGenBuffers(1, &circleVBO);

    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);

    glBindVertexArray(m_CircleVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
}
