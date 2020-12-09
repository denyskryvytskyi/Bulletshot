#pragma once

#include <gdm/gdm.h>

enum class ShapeType
{
    AABB,
    Circle
};

struct CollisionShape
{
    CollisionShape(ShapeType type) : m_Type(type) {}

    ShapeType m_Type;
};

typedef std::pair<bool, gdm::vec2> CollisionInfo;