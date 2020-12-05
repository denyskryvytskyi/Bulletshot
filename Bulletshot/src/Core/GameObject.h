#pragma once

#include <gdm/gdm.h>
#include "Renderer.h"

class GameObject
{
public:
    GameObject() = default;
    GameObject(gdm::vec2 pos, gdm::vec2 size, gdm::vec3 color);

    virtual void Draw(Renderer& renderer) = 0;

protected:
    gdm::vec3 m_Color;
    gdm::vec2 m_Position;
    gdm::vec2 m_Size;
    bool m_Destroyed;
};

typedef std::shared_ptr<GameObject> StrongGameObjectPtr;