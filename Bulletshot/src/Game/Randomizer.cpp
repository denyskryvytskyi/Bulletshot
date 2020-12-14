#include "bspch.h"
#include "Randomizer.h"

Randomizer::Randomizer()
{
    // Seed generation using time since epoch
    srand(TimeStamp::GetTimeSinceEpochInSeconds());
}

gdm::vec2 Randomizer::GeneratePosition(gdm::vec2 min, gdm::vec2 max)
{
    return gdm::vec2((float)(rand() % (uint16_t)max.x + (uint16_t)min.x), (float)(rand() % (uint16_t)max.y + (uint16_t)min.y));
}

gdm::vec2 Randomizer::GenerateDirection()
{
    gdm::vec2 result = gdm::rotatePoint(GenerateRotationAngle(0.0f, 360.0f), { 1.0f }, { 0.0f });
    return result;
}

gdm::vec2 Randomizer::GenerateRectSize(gdm::vec2 min, gdm::vec2 max)
{
    return gdm::vec2((float)(rand() % (uint16_t)max.x + (uint16_t)min.x), (float)(rand() % (uint16_t)max.y + (uint16_t)min.y));
}

float Randomizer::GenerateRotationAngle(float min, float max)
{
    return rand() % (uint16_t)max + min;
}
