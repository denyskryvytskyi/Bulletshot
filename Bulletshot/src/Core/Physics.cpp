#include "bspch.h"
#include "Physics.h"

#include <glm/glm.hpp>

Physics g_Physics;

void Physics::DoCollisions()
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
                objA->OnCollisionEnter(objA, objB, collisionResult);
                objB->OnCollisionEnter(objA, objB, collisionResult);
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

//void Physics::RegisterObjectWall(const StrongGameObjectPtr& gameobject)
//{
//    m_CollidersWalls.push_back(gameobject);
//    //m_Observers.insert(gameobject);
//    //m_Subject.AddObserver(dynamic_cast<CollisionObserver*>(gameobject));
//}
//
//void Physics::UnregisterObjectWall(const StrongGameObjectPtr& gameobject)
//{
//    auto it = std::find(m_CollidersWalls.begin(), m_CollidersWalls.end(), gameobject);
//
//    if (it != m_CollidersWalls.end())
//    {
//        m_CollidersWalls.erase(it);
//    }
//    //m_Observers.erase(gameobject);
//}
//
//void Physics::RegisterObjectBullet(const StrongGameObjectPtr& gameobject)
//{
//    m_CollidersBullets.push_back(gameobject);
//}
//
//void Physics::UnregisterObjectBullet(const StrongGameObjectPtr& gameobject)
//{
//    std::remove(m_CollidersBullets.begin(), m_CollidersBullets.end(), gameobject);
//    auto it = std::find(m_CollidersBullets.begin(), m_CollidersBullets.end(), gameobject);
//
//    if (it != m_CollidersBullets.end())
//    {
//        m_CollidersBullets.erase(it);
//    }
//}

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
    float circleRadius = circle->GetSize().x / 2.0f;
    gdm::vec2 circleCenter = circle->GetPosition();

    gdm::vec2 rectPos = aabb->GetPosition();
    gdm::vec2 rectSize = aabb->GetSize();
    float angle = gdm::radians(aabb->GetRotation());

    // rotation circle
    gdm::vec2 rectCenter = rectPos + rectSize / 2;
    gdm::vec2 rotatedCircle = RotatePoint(angle, circleCenter, rectCenter);
   /* rotatedCircle.x = cos(angle) * (circleCenter.x - rectCenter.x) - sin(angle) * (circleCenter.y - rectCenter.y) + rectCenter.x;
    rotatedCircle.y = sin(angle) * (circleCenter.x - rectCenter.x) + cos(angle) * (circleCenter.y - rectCenter.y) + rectCenter.y;*/

    //
    gdm::vec2 intersectPoint = gdm::clamp(rotatedCircle, rectPos, rectPos + rectSize);
    //

    // Rotate back intersectionPoint
    angle = -angle;
    gdm::vec2 retInter = RotatePoint(angle, intersectPoint, rectCenter);
   /* retInter.x = cos(angle) * (intersectPoint.x - rectCenter.x) - sin(angle) * (intersectPoint.y - rectCenter.y) + rectCenter.x;
    retInter.y = sin(angle) * (intersectPoint.x - rectCenter.x) + cos(angle) * (intersectPoint.y - rectCenter.y) + rectCenter.y;*/
    //

    gdm::vec2 difference = retInter - circleCenter;

    if (gdm::magnitude(difference) <= circleRadius)
        return std::make_pair(true, difference);
    else
        return std::make_pair(false, gdm::vec2(0.0f, 0.0f));
}


gdm::vec2 Physics::GetReflectionVector(gdm::vec2 dir, gdm::vec2 pos, CollisionInfo info)
{
    //gdm::vec2 intersectPoint = std::get<2>(info);
    //gdm::vec2 distance(pos.x - intersectPoint.x, pos.y - intersectPoint.y);
    //gdm::vec2 normal(distance.x, distance.y);

    gdm::vec2 normal = gdm::normalize(std::get<1>(info));
    //normal = gdm::normalize(normal);

    // r = d - 2(d . n) * n , where d . n is dot product
    return (dir - normal * (gdm::dot(dir, normal) * 2));
    //return gdm::vec2();
}


gdm::vec2 Physics::RotatePoint(float angle, gdm::vec2 point, gdm::vec2 origin)
{
    gdm::vec2 rotatedP(0.0f);
    rotatedP.x = cos(angle) * (point.x - origin.x) - sin(angle) * (point.y - origin.y) + origin.x;
    rotatedP.y = sin(angle) * (point.x - origin.x) + cos(angle) * (point.y - origin.y) + origin.y;

    return rotatedP;
}