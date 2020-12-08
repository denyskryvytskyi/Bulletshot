#pragma once

#include <gdm/gdm.h>
#include "Renderer.h"
#include "Core/ColliderComponent.h"
#include "CommonTypes.h"

class GameObject
{
public:
    GameObject() = default;
    GameObject(gdm::vec2 pos, gdm::vec2 size, gdm::vec3 color, ShapeType shape);

    virtual void Draw(Renderer& renderer) = 0;
    virtual void OnCollisionEnter(GameObject* objA, GameObject* objB, const CollisionInfo& collisionInfo) = 0;

    virtual CollisionShape GetShape() const = 0;
    virtual float GetRotation() const = 0;

    const gdm::vec2& GetPosition() const { return m_Position; }
    const gdm::vec2& GetSize() const { return m_Size; }
    bool IsDestroyed() const { return m_Destroyed; };

protected:
    gdm::vec3 m_Color;
    gdm::vec2 m_Position;
    gdm::vec2 m_Size;
    ShapeType m_Shape;
    bool m_Destroyed;
};