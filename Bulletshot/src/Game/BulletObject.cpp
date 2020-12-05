#include "bspch.h"
#include "BulletObject.h"

BulletObject::BulletObject(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime, float radius, gdm::vec3 color)
    : GameObject(pos, { radius }, color)
    , m_Dir(dir), m_Speed(speed), m_TimeToSpawn(time), m_Lifetime(lifetime), m_Radius(radius), m_Spawned(false)
{
}

void BulletObject::Draw(Renderer& renderer)
{
    renderer.DrawCircle(m_Position, m_Radius, m_Color);
}

void BulletObject::Update(float dt)
{
    if (m_Destroyed)
        return;

    // Calculate time from bullet generation
    float elapsedTime = m_Timer.elapsed();

    if (!m_Spawned)
    {
        if (elapsedTime >= m_TimeToSpawn)
        {
            m_Spawned = true;
            m_Timer.restart();
        }
        else 
        {
            return;
        }
    }

    // Calculate time from bullet spawning
    elapsedTime = m_Timer.elapsed();
    if (elapsedTime >= m_Lifetime)
    {
        m_Destroyed = true;
        return;
    }

    m_Position += (m_Dir * m_Speed) * dt;
}
