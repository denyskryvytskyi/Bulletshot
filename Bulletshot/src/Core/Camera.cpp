#include "bspch.h"
#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(gdm::orthographic(left, right, bottom, top, -1.0f, 1.0f))
{
}

void Camera::SetProjection(float left, float right, float bottom, float top)
{
    m_ProjectionMatrix = gdm::orthographic(left, right, bottom, top, -1.0f, 1.0f);
}
