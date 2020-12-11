#pragma once

#include "WallObject.h"

class WallManager
{
public:
    WallManager() = default;
    ~WallManager();

    void Update();
    void Cleanup();
    void CreateWall(gdm::vec2 pos, gdm::vec2 size, float rotationAngle);

    const std::vector<WallObject*>& GetWalls() { return m_WallObjects; }

private:
    std::vector<WallObject*> m_WallObjects;
};

