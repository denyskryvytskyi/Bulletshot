#pragma once

#include <functional>
#include <gdm/gdm.h>

enum class EDirection
{
    Up,
    Right,
    Down,
    Left
};

typedef std::tuple<bool, EDirection, gdm::vec2> CollisionInfo;