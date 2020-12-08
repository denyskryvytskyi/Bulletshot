#include "bspch.h"
#include "WallObject.h"

WallObject::WallObject(gdm::vec2 pos, gdm::vec2 size, float rotationAngle, gdm::vec3 color, ShapeType shape)
    : GameObject(pos, size, color, shape)
    , m_RotationAngle(rotationAngle)
{
}

void WallObject::Draw(Renderer& renderer)
{
    if (!m_Destroyed)
    {
        renderer.DrawQuad(m_Position, m_Size, m_RotationAngle, m_Color);
    }
}

void WallObject::OnCollisionEnter(GameObject* objA, GameObject* objB, const CollisionInfo& collisionInfo)
{
    m_Destroyed = true;
}
