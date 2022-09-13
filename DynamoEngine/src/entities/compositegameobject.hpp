// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of DynamoEngine.
//
// DynamoEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DynamoEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DynamoEngine.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "DynamoEngine/src/core/timestep.hpp"
#include "DynamoEngine/src/entities/gameobject.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class CompositeGameObject
{
public:
    virtual ~CompositeGameObject() = default;

    int AddObject(GameObject *object);
    void RemoveObject(int objectId);
    GameObject *GetObject(int objectId);

    virtual void SetPosition(const glm::vec2 &position);
    virtual void AddPosition(const glm::vec2 &displacement);
    virtual void SetVelocity(const glm::vec2 &velocity);
    virtual void AddVelocity(const glm::vec2 &velocity);
    virtual void Rotate(float angle);

    const glm::vec2 GetPosition() const { return pos; }
    const glm::vec2 GetVelocity() const { return vel; }

    void Render();

    virtual void Update(const Timestep &dt);

protected:
    glm::vec2 pos{0.f};
    glm::vec2 vel{0.f};

    std::vector<std::unique_ptr<GameObject>> objects{};
    int objectId = 0;
};