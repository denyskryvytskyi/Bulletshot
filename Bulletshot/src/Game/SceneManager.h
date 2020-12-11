#pragma once

#include <gdm/gdm.h>

struct BulletStartupInfo
{
    BulletStartupInfo(gdm::vec2 pos, gdm::vec2 dir, float speed = 200.0f, float timeToSpawn = 3.0f, float lifeTime = 5.0f)
        : Position(pos), Direction(dir), Speed(speed), TimeToSpawn(timeToSpawn), LifeTime(lifeTime)
    {}

    gdm::vec2 Position;
    gdm::vec2 Direction;
    float Speed;
    float TimeToSpawn;
    float LifeTime;
};

struct WallStartupInfo
{
    WallStartupInfo(gdm::vec2 pos, gdm::vec2 size, float rotation)
        : Position(pos), Size(size), Rotation(rotation)
    {}

    gdm::vec2 Position;
    gdm::vec2 Size;
    float Rotation;
};

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    void Init(float screenWidth, float screenHeight);
    void CreateScene(int32_t wallsCount = 10, int32_t bulletsCount = 0);
    void Cleanup();

    const std::vector<BulletStartupInfo>& GetBulletsInfo() const { return m_BulletsStartupInfo; }
    const std::vector<WallStartupInfo>& GetWallsInfo() const { return m_WallsStartupInfo; }

private:
    std::vector<BulletStartupInfo> m_BulletsStartupInfo;
    std::vector<WallStartupInfo> m_WallsStartupInfo;

    float m_ScreenWidth;
    float m_ScreenHeight;
};