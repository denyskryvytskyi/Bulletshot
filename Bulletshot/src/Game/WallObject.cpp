#include "bspch.h"
#include "WallObject.h"

WallObject::WallObject(gdm::vec2 pos, gdm::vec2 size, float rotationAngle, gdm::vec3 color, ShapeType shape)
    : GameObject(pos, size, color, shape)
    , m_RotationAngle(gdm::radians(rotationAngle))
    , m_RectCenter(pos + size / 2.0f)
{
}

void WallObject::Draw(Renderer& renderer)
{
    if (!m_Destroyed)
    {
        renderer.DrawQuad(m_Position, m_Size, m_RotationAngle, m_Color);
    }
}

void WallObject::OnCollisionEnter(CollisionInfo info)
{
    m_Destroyed = std::get<0>(info);
}
