#pragma once

#include <gdm/gdm.h>
#include "BulletObject.h"

class BulletManager
{
public:
    BulletManager() = default;
    ~BulletManager();

    void Update(float dt);
    void Fire(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifetime);

    const std::vector<BulletObject*>& GetBulletObjects() const;

private:
    std::vector<BulletObject*> m_BulletObjects;
    std::vector<BulletObject*> m_SharedResource;
    std::mutex m_Mutex;
};