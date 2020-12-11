#include "bspch.h"
#include "SceneManager.h"
#include "Randomizer.h"


SceneManager::SceneManager()
    : m_ScreenWidth(0), m_ScreenHeight(0)
{
}

SceneManager::~SceneManager()
{
    Cleanup();
}

void SceneManager::Init(float screenWidth, float screenHeight)
{
    m_ScreenWidth = screenWidth;
    m_ScreenHeight = screenHeight;
}

void SceneManager::CreateScene(int32_t wallsCount, int32_t bulletsCount)
{
    Cleanup(); // remove previous objects

    Randomizer randomizer;

    // Generate random wall info
    for (uint32_t i = 0; i < wallsCount; i++)
    {
        m_WallsStartupInfo.emplace_back(WallStartupInfo(randomizer.GeneratePosition({ 50.0f, 50.0f }, { m_ScreenWidth, m_ScreenHeight }),
            randomizer.GenerateRectSize({ 50.0f, 100.0f }, { 10.0f, 200.0f }),
            randomizer.GenerateRotationAngle(-90.0f, 90.0f)));
    }

    // Generate random bullets info
    for (uint32_t i = 0; i < bulletsCount; i++)
    {
        m_BulletsStartupInfo.emplace_back(BulletStartupInfo(randomizer.GeneratePosition({ 50.0f, 50.0f }, { m_ScreenWidth, m_ScreenHeight }),
            randomizer.GenerateDirection({ -1.0f, -1.0f }, { 1.0f, 1.0f })));
    }
}

void SceneManager::Cleanup()
{
    m_BulletsStartupInfo.clear();
    m_WallsStartupInfo.clear();
}
