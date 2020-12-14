#include "bspch.h"
#include "BulletObject.h"
#include "Core/Physics.h"
#include "Game.h"

BulletObject::BulletObject(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime, float radius, gdm::vec3 color, ShapeType shape)
    : GameObject(pos, { radius * 2.0f }, color, shape)
    , m_Dir(dir), m_Speed(speed), m_TimeToSpawn(time), m_Lifetime(lifetime), m_Radius(radius), m_Spawned(false)
{
}

void BulletObject::Draw(Renderer& renderer)
{
    if (m_Spawned)
    {
        renderer.DrawCircle(m_Position, m_Radius, m_Color);
    }
}

void BulletObject::Update(float dt)
{
    if (m_Destroyed)
        return;

    // Calculate time from bullet generation
    float elapsedTime = m_Timer.Elapsed();

    if (!m_Spawned)
    {
        if (elapsedTime >= m_TimeToSpawn)
        {
            m_Spawned = true;
            m_Timer.Restart();
            Game::OnGameobjectSpawned(this);
        }
        else 
        {
            return;
        }
    }

    // Calculate time from bullet spawning
    elapsedTime = m_Timer.Elapsed();
    if (elapsedTime >= m_Lifetime)
    {
        m_Destroyed = true;
        return;
    }

    m_Position += (m_Dir * m_Speed) * dt;
}

void BulletObject::OnCollisionEnter(CollisionInfo info)
{
    gdm::vec2 differenceVector = std::get<1>(info);

    gdm::vec2 oldDir = m_Dir;
    m_Dir = Physics::GetReflectionVector(m_Dir, differenceVector);

    // Calculate penetration
    float penetrationX = (m_Radius - std::abs(differenceVector.x));
    float penetrationY = (m_Radius - std::abs(differenceVector.y));

    // Horizontal
    if (penetrationX != m_Radius)
    {
        if (oldDir.x > m_Dir.x) // new dir is left
        {
            m_Position.x -= penetrationX; // move bullet to left
        }
        else // new dir is right
        {
            m_Position.x += penetrationX; // move bullet to right
        }
    }
    // Vertical
    if (penetrationY != m_Radius)
    {
        if (oldDir.y > m_Dir.y) // new dir is down
        {
            m_Position.y -= penetrationY; // move bullet back down
        }
        else // new dir is up
        {
            m_Position.y += penetrationY; // move bullet back up
        }
    }
}
