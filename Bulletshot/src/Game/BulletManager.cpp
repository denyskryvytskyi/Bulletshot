#include "bspch.h"
#include "BulletManager.h"
#include "Game.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
    m_BulletObjects.clear();
}

void BulletManager::Update(float dt)
{
    static int32_t fails;
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
    else
    {
        ++fails;
    }

    //std::lock_guard<std::mutex> lock(g_Mutex);
    for (auto bulletIterator = m_BulletObjects.begin(); bulletIterator != m_BulletObjects.end();)
    {
        if ((*bulletIterator)->IsDestroyed())
        {
            Game::OnGameobjectDestroyed((*bulletIterator));
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
    //m_BulletObjects.push_back(bullet);
    m_SharedResource.push_back(bullet);
}

const std::vector<BulletObject*>& BulletManager::GetBulletObjects() const
{
    return m_BulletObjects;
}