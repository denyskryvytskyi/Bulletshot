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

void SceneManager::CreateScene(uint32_t wallsCount, uint32_t bulletsCount)
{
    Cleanup(); // remove previous objects

    Randomizer randomizer;

    // Generate random wall info
    for (uint32_t i = 0; i < wallsCount; i++)
    {
        m_WallsStartupInfo.emplace_back(WallStartupInfo(randomizer.GeneratePosition({ 10.0f, 10.0f }, { m_ScreenWidth - 10.0f, m_ScreenHeight - 10.0f}),
            randomizer.GenerateRectSize({ 50.0f, 10.0f }, { 300.0f, 30.0f }),
            randomizer.GenerateRotationAngle(-90.0f, 90.0f)));
    }

    // Generate random bullets info
    for (uint32_t i = 0; i < bulletsCount; i++)
    {
        m_BulletsStartupInfo.emplace_back(BulletStartupInfo(randomizer.GeneratePosition({ 50.0f, 50.0f }, { m_ScreenWidth, m_ScreenHeight }),
            randomizer.GenerateDirection()));
    }
}

void SceneManager::Cleanup()
{
    m_BulletsStartupInfo.clear();
    m_WallsStartupInfo.clear();
}
