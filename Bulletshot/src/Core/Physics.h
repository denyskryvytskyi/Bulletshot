#pragma once

#include "GameObject.h"

enum class CollisionType
{
    AABB_Circle,
    NotSupported
};

class Physics
{
public:

    void Cleanup();
    void DoCollisions(float dt);

    void RegisterObject(GameObject* gameobject);
    void UnregisterObject(GameObject* gameobject);

    // defferenceVector - distance beetween circle center and intersection(reflection) point
    static gdm::vec2 GetReflectionVector(gdm::vec2 dir, gdm::vec2 differenceVector);

private:
    CollisionType DetectCollisionType(CollisionShape colliderA, CollisionShape colliderB) const;

    // AABB - Circle collision
    CollisionInfo CheckCollision(const GameObject* aabb, const GameObject* circle);

    //gdm::vec2 RotatePoint(float angle, gdm::vec2 point, gdm::vec2 origin);

private:
    std::vector<GameObject*> m_Colliders;
};

extern Physics g_Physics;