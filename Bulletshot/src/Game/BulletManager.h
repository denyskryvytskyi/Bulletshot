#pragma once

#include <gdm/gdm.h>
#include "BulletObject.h"

class BulletManager
{
public:
    BulletManager();
    ~BulletManager();

    // Called only from main thread
    void Update(float dt);

    // Called from different threads
    void Fire(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime);

    void Cleanup();

    const std::vector<BulletObject*>& GetBulletObjects() const;

private:

    // Access only from main thread
    std::vector<BulletObject*> m_BulletObjects;

    // Access from different threads
    std::vector<BulletObject*> m_SharedResource;

    std::mutex m_Mutex;
    std::condition_variable m_ForceUpdateCV;

    // Count of failed attempt to access shared resource from main thread (in update function)
    int32_t m_FailAttemptsUpdateWithSharedCount;
    const int32_t m_LimitFailsCount;
};