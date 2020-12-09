#pragma once

#include "Core/Timer.h"
#include "Core/GameObject.h"

class BulletObject : public GameObject
{
public:
    BulletObject(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime, float radius = 5.0f, gdm::vec3 color = { 1.0f, 1.0f, 0.0f }, ShapeType shapeType = ShapeType::Circle);

    void Draw(Renderer& renderer) override;
    void Update(float dt);
    
    void OnCollisionEnter(CollisionInfo info) override;
    float GetRotation() const override { return 0; }

    CollisionShape GetShape() const override { return m_Shape; }

private:
    gdm::vec2 m_Dir;
    Timer m_Timer;
    float m_Speed;
    float m_TimeToSpawn;
    float m_Lifetime;
    float m_Radius;
    bool m_Spawned;
};

typedef std::shared_ptr<BulletObject> StrongBulletObjectPtr;