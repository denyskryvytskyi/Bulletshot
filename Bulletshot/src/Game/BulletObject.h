#pragma once

#include "Core/Timer.h"
#include "Core/GameObject.h"

class BulletObject : public GameObject
{
public:
    BulletObject(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime, float radius = 10.0f, gdm::vec3 color = { 1.0f, 1.0f, 0.0f }, ShapeType shapeType = ShapeType::Circle);

    void Draw(Renderer& renderer) override;
    void Update(float dt);
    
    void OnCollisionEnter(GameObject* objA, GameObject* objB, const CollisionInfo& collisionInfo) override;
    float GetRotation() const override { return 0; }

    bool IsDestroyed() const { return m_Destroyed; };
    CollisionShape GetShape() const override { return m_Shape; }

private:
    gdm::vec2 m_Dir;
    Timer m_Timer;
    //CircleShape m_Shape;
    float m_Speed;
    float m_TimeToSpawn;
    float m_Lifetime;
    float m_Radius;
    bool m_Spawned;
};