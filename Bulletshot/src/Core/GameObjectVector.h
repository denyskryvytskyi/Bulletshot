#pragma once

#include "GameObject.h"

class GameObjectVector
{
public:
    GameObjectVector() = default;
    ~GameObjectVector();

    void PushGameObject(GameObject* gameobject);
    void PopGameObject(GameObject* gameobject);

private:
    std::vector<GameObject*> m_GameObjects;
};