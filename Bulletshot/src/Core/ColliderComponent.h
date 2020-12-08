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

struct AABBShape : public CollisionShape
{
    AABBShape(gdm::vec2 pos, gdm::vec2 size, ShapeType type = ShapeType::AABB)
        : CollisionShape(type)
        , m_Pos(pos), m_Size(size)
    {}

    gdm::vec2 m_Pos;
    gdm::vec2 m_Size;
};

struct CircleShape : public CollisionShape
{
    CircleShape(gdm::vec2 pos, float radius, ShapeType type = ShapeType::Circle)
        : CollisionShape(type)
        , m_Pos(pos), m_Radius(radius)
    {}

    gdm::vec2 m_Pos;
    float m_Radius;
};

//enum class CollisionShape
//{
//    None,
//    Circle,
//    Rect
//};
//
//class ColliderComponent
//{
//public:
//    ColliderComponent(const CollisionShape& shape)
//        : m_Shape(shape)
//    {}
//
//    CollisionShape GetShape() const { return m_Shape; }
//
//private:
//    CollisionShape m_Shape;
//};