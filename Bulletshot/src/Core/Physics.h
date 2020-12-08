#pragma once

#include "CommonTypes.h"
#include "Subject.h"
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

    //Subject<CollisionObserver>& GetSubject() { return m_Subject; };

    static gdm::vec2 GetReflectionVector(gdm::vec2 dir, gdm::vec2 pos, gdm::vec2 intersectPoint);
    static gdm::vec2 CollisionResolution(gdm::vec2 dir, gdm::vec2 pos, CollisionInfo info);

private:
    CollisionType DetectCollisionType(CollisionShape colliderA, CollisionShape colliderB) const;

    // AABB - Circle collision
    CollisionInfo CheckCollision(const GameObject* aabb, const GameObject* circle);

    void NotifyObservers();

    EDirection VectorDirection(gdm::vec2 target);

private:
    //Subject<CollisionObserver> m_Subject;

    std::vector<GameObject*> m_Colliders;
    std::set<CollisionObserver*> m_Observers;
};

extern Physics g_Physics;