#include "bspch.h"
#include "GameObject.h"

GameObject::GameObject(gdm::vec2 pos, gdm::vec2 size, gdm::vec3 color)
    : m_Position(pos), m_Size(size), m_Color(color), m_Destroyed(false)
{
}
