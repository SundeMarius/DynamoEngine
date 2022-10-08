#pragma once

#include "DynamoEngine/src/entities/gameobject.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <memory>

class GameObjectContainer
{
public:
    std::size_t AddObject(GameObject *object);
    void RemoveObject(std::size_t objectId);
    GameObject *GetObject(std::size_t objectId) const;
    GameObject *ReleaseObject(std::size_t objectId);
    void ResetObject(std::size_t objectId, GameObject *object);

    void Render();

    void Update(const Timestep &dt);

private:
    std::vector<std::unique_ptr<GameObject>> objects{};
    std::size_t objectId = 0;
};