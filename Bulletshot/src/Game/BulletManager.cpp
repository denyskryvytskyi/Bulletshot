#include "bspch.h"
#include "BulletManager.h"

std::mutex g_Mutex;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
    m_BulletObjects.clear();
}

void BulletManager::Update(float dt)
{
    std::lock_guard<std::mutex> lock(g_Mutex);
    for (auto bulletIterator = m_BulletObjects.begin(); bulletIterator != m_BulletObjects.end();)
    {
        if ((*bulletIterator)->IsDestroyed())
        {
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
    StrongBulletPtr bullet = std::make_shared<BulletObject>(pos, dir, speed, time, lifetime);

    std::lock_guard<std::mutex> lock(g_Mutex);
    m_BulletObjects.push_back(bullet);
}

const std::vector<StrongBulletPtr>& BulletManager::GetBulletObjects() const
{
    return m_BulletObjects;
}
