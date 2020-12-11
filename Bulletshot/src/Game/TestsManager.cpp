#include "bspch.h"
#include "TestsManager.h"

int32_t TestsManager::m_WallsCount = 0;
int32_t TestsManager::m_BulletsCount = 0;
bool TestsManager::m_GenerateObjects = false;
bool TestsManager::m_CleanupScene = false;
bool TestsManager::m_AllowMTStabilityStressTest = false;

void TestsManager::ToggleGenerateObjects(const int32_t wallsCount, const int32_t bulletsCount)
{
    m_WallsCount = wallsCount;
    m_BulletsCount = bulletsCount;
    m_GenerateObjects = true;
}

void TestsManager::ToggleGenerateObjects()
{
    m_GenerateObjects = !m_GenerateObjects;
}

void TestsManager::ToggleCleanupScene()
{
    m_CleanupScene = true;
}

void TestsManager::ToggleMTStressTest()
{
    m_AllowMTStabilityStressTest = !m_AllowMTStabilityStressTest;
}
