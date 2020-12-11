#include "bspch.h"
#include "WallManager.h"
#include "Game.h"

WallManager::~WallManager()
{
    Cleanup();
}

void WallManager::Update()
{
    for (auto wallIterator = m_WallObjects.begin(); wallIterator != m_WallObjects.end();)
    {
        if ((*wallIterator)->IsDestroyed())
        {
            Game::OnGameobjectDestroyed(*wallIterator);
            delete* wallIterator;
            wallIterator = m_WallObjects.erase(wallIterator);
        }
        else
        {
            ++wallIterator;
        }
    }
}

void WallManager::Cleanup()
{
    for (int32_t i = 0; i < m_WallObjects.size(); ++i)
    {
        delete m_WallObjects[i];
    }
    m_WallObjects.clear();
}

void WallManager::CreateWall(gdm::vec2 pos, gdm::vec2 size, float rotationAngle)
{
    WallObject* wall = new WallObject(pos, size, rotationAngle);
    m_WallObjects.push_back(wall);

    Game::OnGameobjectSpawned(wall);
}
