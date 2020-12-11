#include "bspch.h"
#include "SceneManager.h"

SceneManager::~SceneManager()
{
    Cleanup();
}

void SceneManager::CreateScene(int32_t wallsCount, int32_t bulletsCount)
{
    // Generate random infos
}

void SceneManager::Cleanup()
{
    m_BulletsStartupInfo.clear();
    m_WallsStartupInfo.clear();
}
