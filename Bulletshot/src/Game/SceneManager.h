#pragma once

#include <gdm/gdm.h>

struct BulletStartupInfo
{
    gdm::vec2 Position;
    gdm::vec2 Direction;
    float Speed;
    float TimeToSpawn;
    float LifeTime;
};

struct WallStartupInfo
{
    gdm::vec2 Position;
    gdm::vec2 Size;
    float rotation;
};

class SceneManager
{
public:
    SceneManager() = default;
    ~SceneManager();

    void CreateScene(int32_t wallsCount = 10, int32_t bulletsCount = 0);
    void Cleanup();

private:
    std::vector<BulletStartupInfo> m_BulletsStartupInfo;
    std::vector<WallStartupInfo> m_WallsStartupInfo;
};