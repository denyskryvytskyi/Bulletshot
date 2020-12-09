#pragma once

#include <gdm/gdm.h>

class Camera
{
public:
    Camera() = default;
    Camera(float left, float right, float bottom, float top);

    void SetProjection(float left, float right, float bottom, float top);
    const gdm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

private:
    gdm::mat4 m_ProjectionMatrix;
};

