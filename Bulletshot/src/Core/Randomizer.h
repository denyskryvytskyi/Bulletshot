#pragma once

#include <gdm/gdm.h>

class Randomizer
{
    void GenerateScene();

    gdm::vec2 GeneratePosition(float min, float max);
    gdm::vec2 GenerateDirection(float min, float max);

    gdm::vec2 GenerateRectSize(float min, float max);
    float GenerateRotationAngle(float min, float max);

};