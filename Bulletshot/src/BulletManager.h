#pragma once

#include <gdm/gdm.h>

class BulletManager
{
public:
    BulletManager();
    ~BulletManager();

    void Update(float dt);
    void Fire(gdm::vec2 pos, gdm::vec2 dir, float speed, float time, float lifeTime);
};

