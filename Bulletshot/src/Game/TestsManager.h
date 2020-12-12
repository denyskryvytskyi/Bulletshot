#pragma once

class TestsManager
{
public:
    TestsManager() = default;

    static void ToggleGenerateObjects(const uint32_t wallsCount, const uint32_t bulletsCount);
    static void ToggleGenerateObjects();
    static void ToggleCleanupScene(bool toggle);
    static void ToggleMTStressTest();

public:
    static uint32_t m_WallsCount;
    static uint32_t m_BulletsCount;
    static bool m_GenerateObjects;
    static bool m_CleanupScene;
    static bool m_AllowMTStabilityStressTest;
};