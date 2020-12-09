#include "bspch.h"
#include "BulletManager.h"
#include "Game.h"

BulletManager::~BulletManager()
{
    for (int32_t i = 0; i < m_BulletObjects.size(); i++)
    {
        delete m_BulletObjects[i];
    }
    m_BulletObjects.clear();
}

void BulletManager::Update(float dt)
{
    if (m_Mutex.try_lock())
    {
        // update bullets with shared resource
        for (auto sharedBullet : m_SharedResource)
        {
            m_BulletObjects.push_back(sharedBullet);
        }
        m_SharedResource.clear();
        m_Mutex.unlock();
    }

    for (auto bulletIterator = m_BulletObjects.begin(); bulletIterator != m_BulletObjects.end();)
    {
        if ((*bulletIterator)->IsDestroyed())
        {
            Game::OnGameobjectDestroyed(*bulletIterator);
            delete *bulletIterator;
            bulletIterator = m_BulletObjects.erase(bulletIterator);
        }
        else
        {
            (*bulletIterator)->Update(dt);
            ++bulletIterator;
        }
    }
}

void BulletManager::Fire(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime)
{
    BulletObject* bullet = new BulletObject(pos, dir, speed, time, lifetime);

    std::lock_guard<std::mutex> lock(m_Mutex);
    m_SharedResource.push_back(bullet);
}

const std::vector<BulletObject*>& BulletManager::GetBulletObjects() const
{
    return m_BulletObjects;
}
