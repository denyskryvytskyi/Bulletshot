#pragma once

#include "Core/GameObject.h"
#include "Core/Physics.h"

class WallObject : public GameObject
{
public:
    WallObject(gdm::vec2 pos, gdm::vec2 size, float rotationAngle, gdm::vec3 color = { 0.0f, 1.0f, 1.0f }, ShapeType shapeType = ShapeType::AABB);

    void Draw(Renderer& renderer) override;

    void OnCollisionEnter(CollisionInfo info) override;
    float GetRotation() const override { return m_RotationAngle; }
    const gdm::vec2& GetShapeCenter() const override { return m_RectCenter; }

    CollisionShape GetShape() const override { return m_Shape; }

private:
    float m_RotationAngle; // in radians
    gdm::vec2 m_RectCenter;
};