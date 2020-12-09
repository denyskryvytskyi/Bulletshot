#include "bspch.h"
#include "Physics.h"

Physics g_Physics;

void Physics::DoCollisions(float dt)
{
    for (int32_t i = 0; i < m_Colliders.size(); ++i)
    {
        for (int32_t j = i + 1; j < m_Colliders.size(); ++j)
        {
            GameObject* objA = m_Colliders[i];
            GameObject* objB = m_Colliders[j];

            CollisionShape shapeA = objA->GetShape();
            CollisionShape shapeB = objB->GetShape();

            CollisionInfo collisionResult;
            switch (DetectCollisionType(shapeA, shapeB))
            {
            case CollisionType::AABB_Circle:
                collisionResult = shapeA.m_Type == ShapeType::AABB ? CheckCollision(objA, objB) : CheckCollision(objB, objA);
                break;
            default:
                // collision type isn't supported
                continue;
            }

            if (std::get<0>(collisionResult))
            {
                objA->OnCollisionEnter(collisionResult);
                objB->OnCollisionEnter(collisionResult);
            }
        }
    }
}

void Physics::RegisterObject(GameObject* gameobject)
{
    m_Colliders.push_back(gameobject);
}

void Physics::UnregisterObject(GameObject* gameobject)
{
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), gameobject);

    if (it != m_Colliders.end())
    {
        m_Colliders.erase(it);
    }
}

CollisionType Physics::DetectCollisionType(CollisionShape colliderA, CollisionShape colliderB) const
{
    if ((colliderA.m_Type == ShapeType::AABB && colliderB.m_Type == ShapeType::Circle) ||
        (colliderA.m_Type == ShapeType::Circle && colliderB.m_Type == ShapeType::AABB))
    {
        return CollisionType::AABB_Circle;
    }

    return CollisionType::NotSupported;
}

CollisionInfo Physics::CheckCollision(const GameObject* aabb, const GameObject* circle)
{
    gdm::vec2 circleCenter = circle->GetPosition();
    gdm::vec2 rotatedCircleCenter = circleCenter;

    gdm::vec2 rectPos = aabb->GetPosition();
    gdm::vec2 rectCenter = aabb->GetShapeCenter(); // unrotated
    float angle = aabb->GetRotation();

    // Rotate circle center point
    if (angle != 0)
    {
        rotatedCircleCenter = RotatePoint(angle, circleCenter, rectCenter);
    }

    gdm::vec2 intersectPoint = gdm::clamp(rotatedCircleCenter, rectPos, rectPos + aabb->GetSize());

    // Rotate intersection point
    if (angle != 0)
    {
        angle = -angle;
        intersectPoint = RotatePoint(angle, intersectPoint, rectCenter);
    }

    gdm::vec2 difference = intersectPoint - circleCenter;

    // Compare difference vector and circle radius
    if (gdm::magnitude(difference) <= (circle->GetSize().x / 2.0f))
        return std::make_pair(true, difference);
    else
        return std::make_pair(false, gdm::vec2(0.0f, 0.0f));
}


gdm::vec2 Physics::GetReflectionVector(gdm::vec2 dir, gdm::vec2 differenceVector)
{
    gdm::vec2 normal = gdm::normalize(differenceVector);

    // r = d - 2(d . n) * n , where d . n is dot product
    return (dir - normal * (gdm::dot(dir, normal) * 2));
}


gdm::vec2 Physics::RotatePoint(float angle, gdm::vec2 point, gdm::vec2 origin)
{
    return gdm::vec2(cos(angle) * (point.x - origin.x) - sin(angle) * (point.y - origin.y) + origin.x,
                     sin(angle) * (point.x - origin.x) + cos(angle) * (point.y - origin.y) + origin.y);
}