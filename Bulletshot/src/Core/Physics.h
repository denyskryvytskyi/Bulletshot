#pragma once

#include "CommonTypes.h"
#include "CollisionObserver.h"
#include "GameObject.h"

enum class CollisionType
{
    AABB_Circle,
    NotSupported
};

class Physics
{
public:
    void DoCollisions();

    void RegisterObject(GameObject* gameobject);
    void UnregisterObject(GameObject* gameobject);

    static gdm::vec2 GetReflectionVector(gdm::vec2 dir, gdm::vec2 pos, CollisionInfo info);

private:
    CollisionType DetectCollisionType(CollisionShape colliderA, CollisionShape colliderB) const;

    // AABB - Circle collision
    CollisionInfo CheckCollision(const GameObject* aabb, const GameObject* circle);

    gdm::vec2 RotatePoint(float angle, gdm::vec2 point, gdm::vec2 origin);

private:
    std::vector<GameObject*> m_Colliders;
    std::set<CollisionObserver*> m_Observers;
};

extern Physics g_Physics;