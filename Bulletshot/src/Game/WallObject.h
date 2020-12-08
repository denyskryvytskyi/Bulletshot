#pragma once

#include "Core/Timer.h"
#include "Core/GameObject.h"
#include "Core/Physics.h"

class WallObject : public GameObject
{
public:
    WallObject(gdm::vec2 pos, gdm::vec2 size, float rotationAngle, gdm::vec3 color = { 0.0f, 1.0f, 1.0f }, ShapeType shapeType = ShapeType::AABB);

    void Draw(Renderer& renderer) override;

    bool IsDestroyed() const { return m_Destroyed; };

    void OnCollisionEnter(GameObject* objA, GameObject* objB, const CollisionInfo& collisionInfo) override;
    float GetRotation() const override { return m_RotationAngle; }

    CollisionShape GetShape() const override { return m_Shape; }

private:
    //AABBShape m_Shape;
    float m_RotationAngle; // in degrees
};