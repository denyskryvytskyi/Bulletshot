#pragma once

#include <gdm/gdm.h>
#include "Core/TimeStamp.h"

class Randomizer
{
public:
    Randomizer();

    gdm::vec2 GeneratePosition(gdm::vec2 min, gdm::vec2 max);
    gdm::vec2 GenerateDirection();

    gdm::vec2 GenerateRectSize(gdm::vec2 min, gdm::vec2 max);
    float GenerateRotationAngle(float min, float max);

private:
    TimeStamp m_Timer;
};