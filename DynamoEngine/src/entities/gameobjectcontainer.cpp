#include "gameobjectcontainer.hpp"

std::size_t GameObjectContainer::AddObject(GameObject *object)
{
    objects.emplace_back(object);
    return objectId++;
}
void GameObjectContainer::RemoveObject(std::size_t objectId)
{
    if (objectId < objects.size())
        objects.erase(objects.begin() + objectId);
}
GameObject *GameObjectContainer::GetObject(std::size_t objectId) const
{
    if (objectId < objects.size())
        return objects[objectId].get();
    return nullptr;
}
std::unique_ptr<GameObject> GameObjectContainer::ReleaseObject(std::size_t objectId)
{
    GameObject *object = objects[objectId].release();
    RemoveObject(objectId);
    return std::unique_ptr<GameObject>(object);
}

void GameObjectContainer::ResetObject(std::size_t objectId, GameObject *object)
{
    objects[objectId].reset(object);
}

void GameObjectContainer::Render()
{
    for (const auto &object : objects)
        object->Render();
}

void GameObjectContainer::Update(const Timestep &dt)
{
    for (const auto &object : objects)
        object->Update(dt);
}