#include "bspch.h"
#include "Physics.h"

#include <glm/glm.hpp>

Physics g_Physics;

gdm::vec2 rotate_point(float cx, float cy, float angle, gdm::vec2 p);

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
            }

            if (std::get<0>(collisionResult))
            {
                objA->OnCollisionEnter(objA, objB, collisionResult);
                objB->OnCollisionEnter(objA, objB, collisionResult);
                /*for (auto observer : m_Observers)
                {
                    observer->OnCollision(objA, objB, std::get<1>(collisionResult));
                }*/
                //NotifyObservers();
                //m_Subject.NotifyObservers(&CollisionObserver::OnCollision, objA, objB, std::get<1>(collisionResult));
            }
        }
    }
}

void Physics::RegisterObject(GameObject* gameobject)
{
    m_Colliders.push_back(gameobject);
    //m_Observers.insert(gameobject);
    //m_Subject.AddObserver(dynamic_cast<CollisionObserver*>(gameobject));
}

void Physics::UnregisterObject(GameObject* gameobject)
{
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), gameobject);

    if (it != m_Colliders.end())
    {
        m_Colliders.erase(it);
    }
    //m_Observers.erase(gameobject);
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
    gdm::vec2 circlePos = circle->GetPosition();
    float radius = circle->GetSize().x;
    gdm::vec2 rectSize = aabb->GetSize();


    // Recalculate position if rotation != 0
    gdm::vec2 rectPos = aabb->GetPosition();
    float theta = aabb->GetRotation();

    if (theta != 0)
    {
        gdm::vec2 rectCenter = rectPos + rectSize / 2.0f;
        gdm::vec2 temp = rectCenter / 2;
        gdm::vec2 rotatedPos(0.0f);
        rotatedPos.x = rectCenter.x + (temp.x * cos(theta)) - (temp.y * sin(theta));
        rotatedPos.y = rectCenter.y + (temp.x * sin(theta)) + (temp.y * cos(theta));

        rectPos = rotate_point(rectCenter.x, rectCenter.y, -theta, rectPos);
    }
    
    //

    gdm::vec2 intersectPoint = gdm::clamp(rectPos + rectSize, circlePos, rectPos);
    
    intersectPoint.x = std::max(rectPos.x, std::min(circlePos.x, rectPos.x + rectSize.x));
    intersectPoint.y = std::max(rectPos.y, std::min(circlePos.y, rectPos.y + rectSize.y));

    //float deltaX = circlePos.x - intersectPoint.x;
    //float deltaY = circlePos.y - intersectPoint.y;
    gdm::vec2 difference = intersectPoint - circlePos;

    //bool collision = (deltaX * deltaX + deltaY * deltaY) < (radius * radius);


    // translate point to origin

    //gdm::vec2 aabbPos = aabb->GetPosition();
    ////float theta = aabb->GetRotation();
   

    //// -----------
    //gdm::vec2 center(circle->GetPosition() + circle->GetSize().x);

    //gdm::vec2 aabbHalfExtens(aabb->GetSize().x / 2.0f, aabb->GetSize().y / 2.0f);
    //gdm::vec2 aabbCenter = aabbPos + aabbHalfExtens;

    //// calc with rotation
    ////gdm::vec2 aabbOrigin = aabbPos - aabbCenter;
    ////gdm::vec2 rotated(0.0f);
    ////rotated.x = aabbOrigin.x * cos(theta) - aabbOrigin.y * sin(theta);
    ////rotated.y = aabbOrigin.x * sin(theta) + aabbOrigin.y * cos(theta);

    ////aabbPos = rotated + aabbCenter;
    ////aabbCenter = aabbPos + aabbHalfExtens;
    ////

    //gdm::vec2 difference = center - aabbCenter;
    //gdm::vec2 clamped = gdm::clamp(difference, -aabbHalfExtens, aabbHalfExtens);

    //gdm::vec2 closest = aabbCenter + clamped;
    //difference = closest - center;

    //gdm::vec2 intersectPoint;
    //bool collision = gdm::magnitude(difference) <= circle->GetSize().x;

    if (gdm::magnitude(difference) <= circle->GetSize().x)
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, EDirection::Up, gdm::vec2(0.0f, 0.0f));
}

void Physics::NotifyObservers()
{
    
}

gdm::vec2 Physics::GetReflectionVector(gdm::vec2 dir, gdm::vec2 pos, gdm::vec2 intersectPoint)
{
    //gdm::vec2 distance(pos.x - intersectPoint.x, pos.y - intersectPoint.y);
    //gdm::vec2 normal(distance.x, distance.y);

    //normal = gdm::normalize(normal);

    //// r = d - 2(d . n) * n , where d . n is dot product
    //return (dir - normal * gdm::dot(dir, normal) * 2);
    return gdm::vec2();
}

gdm::vec2 Physics::CollisionResolution(gdm::vec2 olddir, gdm::vec2 pos, CollisionInfo info)
{
    gdm::vec2 newdir = olddir;
    // collision resolution
    EDirection dir = std::get<1>(info);
    gdm::vec2 diff_vector = std::get<2>(info);
    if (dir == EDirection::Left || dir == EDirection::Right) // horizontal collision
    {
        newdir.x = -newdir.x; // reverse horizontal velocity
        //// relocate
        //float penetration = Ball->m_Radius - std::abs(diff_vector.x);
        //if (dir == EDirection::Left)
        //    Ball->m_Position.x += penetration; // move ball to right
        //else
        //    Ball->m_Position.x -= penetration; // move ball to left;
    }
    else // vertical collision
    {
        newdir.y = -newdir.y; // reverse vertical velocity
        //// relocate
        //float penetration = Ball->m_Radius - std::abs(diff_vector.y);
        //if (dir == EDirection::Up)
        //    Ball->m_Position.y -= penetration; // move ball back up
        //else
        //    Ball->m_Position.y += penetration; // move ball back down
    }

    return newdir;
}


EDirection Physics::VectorDirection(gdm::vec2 target)
{
    gdm::vec2 compass[] = {
        gdm::vec2(0.0f, 1.0f),	// up
        gdm::vec2(1.0f, 0.0f),	// right
        gdm::vec2(0.0f, -1.0f),	// down
        gdm::vec2(-1.0f, 0.0f)	// left
    };

    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = gdm::dot(gdm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (EDirection)best_match;
}

gdm::vec2 rotate_point(float cx, float cy, float angle, gdm::vec2 p)
{
    float s = sin(angle);
    float c = cos(angle);

    // translate point back to origin:
    p.x -= cx;
    p.y -= cy;

    // rotate point
    float xnew = p.x * c - p.y * s;
    float ynew = p.x * s + p.y * c;

    // translate point back:
    p.x = xnew + cx;
    p.y = ynew + cy;
    return p;
}