#include "bspch.h"
#include "GameObjectVector.h"

GameObjectVector::~GameObjectVector()
{
    for (GameObject* gameobject : m_GameObjects)
    {
        delete gameobject;
    }
}

void GameObjectVector::PushGameObject(GameObject* gameobject)
{
    m_GameObjects.push_back(gameobject);
}

void GameObjectVector::PopGameObject(GameObject* gameobject)
{
    auto it = std::find(m_GameObjects.begin(), m_GameObjects.end(), gameobject);

    if (it != m_GameObjects.end())
    {
        m_GameObjects.erase(it);
    }
}
