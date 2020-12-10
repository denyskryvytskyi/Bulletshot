#include "bspch.h"
#include "BulletManager.h"
#include "Game.h"

BulletManager::BulletManager()
    : m_FailAttemptsUpdateWithSharedCount(0), m_LimitFailsCount(5)
{
}

BulletManager::~BulletManager()
{
    for (int32_t i = 0; i < m_BulletObjects.size(); ++i)
    {
        delete m_BulletObjects[i];
    }
    m_BulletObjects.clear();
    for (int32_t i = 0; i < m_SharedResource.size(); ++i)
    {
        delete m_SharedResource[i];
    }
    m_SharedResource.clear();
}

void BulletManager::Update(float dt)
{
    if (m_Mutex.try_lock())
    {
        // Update bullets by shared resource
        if (!m_SharedResource.empty())
        {
            m_BulletObjects.insert(m_BulletObjects.end(), m_SharedResource.begin(), m_SharedResource.end());
            m_SharedResource.clear();
        }
        m_FailAttemptsUpdateWithSharedCount = 0;
        m_Mutex.unlock();
        m_ForceUpdateCV.notify_all(); // notify other threads to continue fire bullets
    }
    else
    {
        ++m_FailAttemptsUpdateWithSharedCount;
    }

    for (auto bulletIterator = m_BulletObjects.begin(); bulletIterator != m_BulletObjects.end();)
    {
        if ((*bulletIterator)->IsDestroyed())
        {
            Game::OnGameobjectDestroyed(*bulletIterator);
            delete* bulletIterator;
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

    std::unique_lock<std::mutex> lock(m_Mutex);

    // wait (give access to the main thread) if reached limit of faild attempts to update bullets container by shared resource container
    m_ForceUpdateCV.wait(lock, [this] { return !(m_FailAttemptsUpdateWithSharedCount >= m_LimitFailsCount); });

    m_SharedResource.emplace_back(bullet);
}

const std::vector<BulletObject*>& BulletManager::GetBulletObjects() const
{
    return m_BulletObjects;
}
